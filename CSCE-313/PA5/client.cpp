#include "common.h"
#include "BoundedBuffer.h"
#include "Histogram.h"
#include "common.h"
#include "HistogramCollection.h"
#include "FIFOreqchannel.h"
#include <time.h>
#include <signal.h>
#include <sys/epoll.h>
#include <unordered_map>
#include <thread>
using namespace std;

void timediff(struct timeval& start, struct timeval& end){
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micro seconds" << endl;

}

FIFORequestChannel* create_new_channel (FIFORequestChannel* mainchan){
    char name[1024];
    MESSAGE_TYPE m = NEWCHANNEL_MSG;
    mainchan->cwrite(&m,sizeof(m));
    mainchan->cread(name, 1024);
    FIFORequestChannel* newchan = new FIFORequestChannel(name, FIFORequestChannel::CLIENT_SIDE);
    return newchan;
}

void patient_thread_function(int n, int pno, BoundedBuffer* request_buffer){
    datamsg d(pno, 0.0,1);
    double resp = 0;
    for(int i = 0; i < n; i++)
    {
        /*chan->cwrite(&d,sizeof(datamsg));
        chan->cread(&resp, sizeof(double));
        hc->update(pno, resp);*/
        request_buffer->push((char*)&d, sizeof(datamsg));
        d.seconds += 0.004;


    }
    /* What will the patient threads do? */
}

void worker_thread_function(FIFORequestChannel* chan, BoundedBuffer* request_buffer, HistogramCollection* hc, int mb){
    char buf[1024];
    double resp = 0;

    char recvbuf[mb];
    while(true)
    {
        request_buffer->pop(buf,1024);
        MESSAGE_TYPE*m = (MESSAGE_TYPE*) buf;

        if(*m == DATA_MSG)
        {
            chan->cwrite(buf,sizeof(datamsg));
            chan->cread(&resp, sizeof(double));
            hc->update(((datamsg*)buf)->person,resp);
        }

        else if(*m ==QUIT_MSG)
        {
            chan->cwrite(m, sizeof(MESSAGE_TYPE));
            delete chan;
            break;

        }
        else if(*m ==FILE_MSG)
        {
            filemsg* fm = (filemsg*) buf;
            string fname = (char*) (fm+1);
            int sz = sizeof(filemsg)+ fname.size()+1;
            chan->cwrite(buf, sz);
            chan->cread(recvbuf, mb);

            string recvfname = "recv/" + fname;

            FILE* fp = fopen(recvfname.c_str(),"r+"); //both read and write mode, expects the file to be there already
            fseek(fp,fm->offset , SEEK_SET);
            fwrite(recvbuf,1,fm->length, fp);
            fclose(fp);


        }
    }
}

void file_thread_function(string fname, BoundedBuffer* request_buffer,FIFORequestChannel* chan, int mb)
{
    if(fname == "")//means we're not doing a file transfer
        return;
    //1. Create the file
    string recvfname = "recv/"+fname;

    //make it as long as the original length
    char buf[1024];
    filemsg f(0,0);
    memcpy(buf, &f, sizeof(f));
    strcpy(buf+sizeof(f), fname.c_str());
    chan->cwrite(buf, sizeof(f)+fname.size()+1);//+1 because of null byte
    u_int64_t filelength;
    chan->cread(&filelength, sizeof(filelength));

    //creating the file
    FILE* fp = fopen(recvfname.c_str(), "w");
    fseek(fp, filelength, SEEK_SET);//making the file of length filelength
    fclose(fp);
    //2. Generate all the file messages

    filemsg* fm = (filemsg*) buf;
    u_int64_t remlen = filelength;

    while(remlen>0)
    {
        fm->length = min(remlen,(u_int64_t) mb);
        request_buffer->push(buf, sizeof(filemsg)+fname.size()+1);
        fm->offset +=fm->length;
        remlen -= fm->length;
    }
}


void event_polling_thread(int w, int mb, FIFORequestChannel** wchans, BoundedBuffer* request_buffer, HistogramCollection* hc)
{
    char buf[1024];
    double resp = 0;
    char recvbuf[mb];

    struct epoll_event ev;
    struct epoll_event events[w];

    //create an empty epoll list
    int epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        EXITONERROR("epoll_create1");
    }

    unordered_map<int, int> fd_to_index; //map fds to index so that we know where they are
    vector<vector<char>> state(w);
    //priming + adding each rfd to the list
    int nsent = 0, nrecv = 0;
    for(int i{}; i < w; i++)
    {
        int sz = request_buffer->pop(buf,1024);
        wchans[i]->cwrite(buf, sz);
        state[i] = vector<char> (buf, buf+sz); //record the state[i]
        nsent++;
        int rfd = wchans[i]->getrfd();
    
        fcntl(rfd, F_SETFL, O_NONBLOCK);

        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = rfd;
        fd_to_index[rfd] = i;
        if (epoll_ctl(epollfd, EPOLL_CTL_ADD, rfd, &ev) == -1)
        {
            EXITONERROR("epoll_ctl: listen_sock");
        }
    }

  
    bool quit_recv = false;

    while (true)
    {
        //condition to break while loop after quit message received
        if (quit_recv && nrecv == nsent)
            break;

        int nfds = epoll_wait(epollfd, events, w, -1);
        if (nfds == -1)
        {
            EXITONERROR("epoll_wait");
        }
        for(int i=0; i < nfds; i++)
        {
            int rfd = events[i].data.fd;
            int index = fd_to_index[rfd];

            int resp_sz = wchans[index]->cread(recvbuf, mb);
            nrecv++;

            // process (recvbuf)
            vector<char> req = state[index];
            char* request = req.data();

            //processing the response
            MESSAGE_TYPE* m = (MESSAGE_TYPE*) request;
            if (*m == DATA_MSG)
            {
                hc->update(((datamsg*) request)->person, *(double*)recvbuf);
            }
            else if (*m == FILE_MSG)
            {
                //filemsg* f = (filemsg*) request;
                filemsg* fm = (filemsg*) request;
                string fname = (char*) (fm+1);
                int sz = sizeof(filemsg)+ fname.size()+1;
                // wchans->cwrite(request, sz);
                // wchans->cread(recvbuf, mb);

                string recvfname = "recv/" + fname;

                FILE* fp = fopen(recvfname.c_str(),"r+"); //both read and write mode, expects the file to be there already
                fseek(fp,fm->offset , SEEK_SET);
                fwrite(recvbuf,1,fm->length, fp);
                fclose(fp);

                
            }

            //reuse
            if (quit_recv)
                continue;
            int req_sz = request_buffer->pop(buf, sizeof(buf));
            if (*(MESSAGE_TYPE* ) buf == QUIT_MSG)
            {
                quit_recv = true;
            }
            else
            {
                wchans[index]->cwrite(buf, req_sz);
                state[index] = vector<char> (buf, buf+req_sz);
                nsent++;

            }

        }
    }
}


int main(int argc, char *argv[])
{
    int n = 15000;    //default number of requests per "patient"
    int p = 1;     // number of patients [1,15]
    int w = 200;    //default number of worker threads
    int b = 500; 	// default capacity of the request buffer, you should change this default
	int m = MAX_MESSAGE; 	// default capacity of the message buffer
    srand(time_t(NULL));
    string fname = "";// = "10.csv"; //hardcoded, get rid of later
    bool transfer_file = false;

    int opt = -1;
    while((opt = getopt(argc,argv,"m:n:b:w:p:f:"))!=-1)
    {
        switch (opt)
        {
            case 'm':
                m = atoi(optarg);
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case 'p':
                p = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 'w':
                w = atoi(optarg);
                break;
            case 'f':
                fname = optarg;
                transfer_file = true;
                break;
        }
    }

    if (w > n * p)
    {
        w = n * p;
    }
    
    
    int pid = fork();
    if (pid == 0){
		// modify this to pass along m
        char *args[] = {"./server", "-m", (char *) to_string(m).c_str(),
                        NULL};
        if (execvp(args[0], args) < 0) {
            perror("exec filed");
            exit(0);
        }
        //execl ("server", "server", (char *)NULL);
    }
    
	FIFORequestChannel* chan = new FIFORequestChannel("control", FIFORequestChannel::CLIENT_SIDE);
    BoundedBuffer request_buffer(b);
	HistogramCollection hc;

	//making histograms and adding to the histogram collection hc

	for(int i = 0; i < p; i++)
    {
	    Histogram* h = new Histogram(10,-2.0,2.0);
	    hc.add(h);
    }

	//make worker channels
	FIFORequestChannel** wchans  = new FIFORequestChannel* [w]; //ADDED
	for(int i = 0; i < w;i++)
    {
	    wchans[i] = create_new_channel(chan);
    }
	
	
	
    struct timeval start, end;
    gettimeofday (&start, 0);

    /* Start all threads here */
    thread patient [p];
    if(!transfer_file)
    {
        //thread patient [p];
        for(int i = 0; i < p;i++)
        {
            patient[i] = thread(patient_thread_function,n,i+1, &request_buffer );
        }
       // cout << "DONE PATIENT" <<endl;
    }
    //else
    //{
        thread filethread(file_thread_function, fname, &request_buffer, chan, m);
    //}


    // thread workers[w];
    // for(int i = 0; i < w;i++)
    // {
    //     workers[i] = thread(worker_thread_function, wchans[i],&request_buffer, &hc,m);
    // }

    thread evp (event_polling_thread, w, m, wchans, &request_buffer, &hc);
	

// //	/* Join all threads here */
	if(!transfer_file)
    {
        for(int i = 0; i < p;i++)
        {
            patient[i].join();
        }
    }

	filethread.join();
    cout << "Patient/file threads finished" <<endl;

    // for(int i = 0; i < w;i++)
    // {
    //     MESSAGE_TYPE q = QUIT_MSG;
    //     request_buffer.push ((char*) &q,sizeof(q));
    // }

    // for(int i = 0; i < w;i++)
    // {
    //     workers[i].join();
    // }

    MESSAGE_TYPE q = QUIT_MSG;
    request_buffer.push((char*) &q, sizeof(q));
    evp.join();
    cout << "Worker threads finished" <<endl;

    gettimeofday (&end, 0);

    // print the results
	hc.print ();

    timediff(start, end);
    //MESSAGE_TYPE q = QUIT_MSG;
    chan->cwrite ((char *) &q, sizeof (MESSAGE_TYPE));
    cout << "All Done!!!" << endl;
    delete chan;

    for(int i = 0; i < w; i++)
    {
        //delete fiforequest channel from server side
        wchans[i]->cwrite(&q, sizeof(MESSAGE_TYPE));

        //delete fiforequestchannel from client side
        delete wchans[i];
    }
    delete[] wchans;

    
}
