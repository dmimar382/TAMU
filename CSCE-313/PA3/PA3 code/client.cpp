/*
    Tanzir Ahmed
    Department of Computer Science & Engineering
    Texas A&M University
    Date  : 2/8/19
 */
#include "common.h"
#include <sys/wait.h>
#include "FIFOreqchannel.h"
#include "MQreqchannel.h"
#include "SHMreqchannel.h"
#include <bits/stdc++.h>
#include <sys/time.h>

using namespace std;


int main(int argc, char *argv[]){
    
    int c;
    int buffercap = MAX_MESSAGE;
    int p = 0, ecg = 1;
    double t = -1.0;
    bool isnewchan = false;
    bool isfiletransfer = false;
    string filename;
    string ipcmethod = "f"; //default value is fifo
    int nchannels = 1;


    while ((c = getopt (argc, argv, "p:t:e:m:f:c:i:")) != -1){
        switch (c){
            case 'p':
                p = atoi (optarg);
                break;
            case 't':
                t = atof (optarg);
                break;
            case 'e':
                ecg = atoi (optarg);
                break;
            case 'm':
                buffercap = atoi (optarg);
                break;
            case 'c':
                isnewchan = true;
                nchannels = atoi(optarg);
                break;
            case 'f':
                isfiletransfer = true;
                filename = optarg;
                break;
            case 'i':
                ipcmethod = optarg;
                break;
        }
    }
    
    // fork part
    if (fork()==0){ // child 
	
		char* args [] = {"./server", "-m", (char *) to_string(buffercap).c_str(), "-i", (char*) ipcmethod.c_str(), NULL};
        if (execvp (args [0], args) < 0){
            perror ("exec filed");
            exit (0);
        }
    }

    vector<RequestChannel*> chan_vector;
    vector <string> output_file;
    RequestChannel* control_chan = NULL;
    RequestChannel* chan = control_chan;

    for( int i = 0; i < nchannels; i ++)
    {
        //output_file.push_back("output" + i);
        control_chan = NULL;
        if(ipcmethod == "f")
            control_chan = new FIFORequestChannel("control", FIFORequestChannel::CLIENT_SIDE);
        else if (ipcmethod == "q")
            control_chan = new MQRequestChannel("control", FIFORequestChannel::CLIENT_SIDE);
        else if(ipcmethod == "m")
            control_chan = new SHMRequestChannel("control", FIFORequestChannel::CLIENT_SIDE, buffercap);

        //control_chan_vector.push_back(control_chan);

        chan = control_chan;
        if (isnewchan){
            cout << "Using the new channel everything following" << endl;
            MESSAGE_TYPE m = NEWCHANNEL_MSG;
            control_chan->cwrite (&m, sizeof (m));
            char newchanname [100];
            control_chan->cread (newchanname, sizeof (newchanname));
            if (ipcmethod == "f")
                chan = new FIFORequestChannel (newchanname, RequestChannel::CLIENT_SIDE);
            else if (ipcmethod == "q")
                chan = new MQRequestChannel (newchanname, RequestChannel::CLIENT_SIDE); //more things to be done here
            else if(ipcmethod == "m")
                chan = new SHMRequestChannel (newchanname, RequestChannel::CLIENT_SIDE, buffercap);
            cout << "New channel by the name " << newchanname << " is created" << endl;
            cout << "All further communication will happen through it instead of the main channel" << endl;
        }
        chan_vector.push_back(chan);

    }


    if (!isfiletransfer){   // requesting data msgs
        for(int j = 0; j < nchannels; j++)
        {
            if (t >= 0)
            {    // 1 data point
                cout << "1 data point" << endl;
                datamsg d(p, t, ecg);
                chan_vector.at(j)->cwrite(&d, sizeof(d));
                double ecgvalue;
                chan_vector.at(j)->cread(&ecgvalue, sizeof(double));
                cout << "Ecg " << ecg << " value for patient " << p << " at time " << t << " is: " << ecgvalue
                     << endl;
            }
            else // bulk (i.e., 1K) data requests
            {
                double ts = 0;
                datamsg d(p, ts, ecg);
                double ecgvalue;

                stringstream stringstr;
                stringstr << j;
                ofstream file;
                string outfile = "received/chan" + stringstr.str() + ".txt";

                file.open(outfile);
                struct timeval start, end; //counting the time taken for this funciton
                gettimeofday(&start, NULL);

                for (int i = 0; i < 1000; i++) {
                    chan_vector.at(j)->cwrite(&d, sizeof(d));
                    chan_vector.at(j)->cread(&ecgvalue, sizeof(double));
                    d.seconds += 0.004; //increment the timestamp by 4ms
                    file << ecgvalue << endl;
                }

                gettimeofday(&end,
                             NULL); //https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/

                // Calculating total time taken by the program.
                double time_taken;

                time_taken = (end.tv_sec - start.tv_sec) * 1e6;
                time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

                cout << "Time taken by program is : " << fixed << time_taken << setprecision(6);
                cout << " sec" << endl;
            }

        }

    }

    else if (isfiletransfer){
        // part 2 requesting a file



        filemsg f(0, 0);  // special first message to get file size
        int to_alloc = sizeof(filemsg) + filename.size() + 1; // extra byte for NULL
        char *buf = new char[to_alloc];
        memcpy(buf, &f, sizeof(filemsg));
        strcpy(buf + sizeof(filemsg), filename.c_str());
        chan->cwrite(buf, to_alloc);
        __int64_t filesize;
        chan->cread(&filesize, sizeof(__int64_t));
        cout << "File size: " << filesize << endl;

        //int transfers = ceil (1.0 * filesize / MAX_MESSAGE);
        filemsg *fm = (filemsg *) buf;
        //__int64_t rem = filesize/nchannels;
        string outfilepath = string("received/") + filename;
        FILE *outfile = fopen(outfilepath.c_str(), "wb");
        fm->offset = 0;
        char *recv_buffer = new char[MAX_MESSAGE];

        //cout << "file size is: " <<filesize <<endl;
        //cout << "file/chan size is: " <<filesize/nchannels <<endl;

        for (int j = 0; j < nchannels; j++)
        {

            struct timeval start1, end1; //counting the time taken for this funciton
            gettimeofday(&start1, NULL);
            //cout <<fm->offset << "IS THE OFFSET " <<endl;
            __int64_t rem = filesize/nchannels;

            while (rem > 0)
            {

                fm->length = (int) min(rem, (__int64_t) MAX_MESSAGE);
//                cout << fm->length <<endl;
//                cout << sizeof(recv_buffer) <<endl;
//                cout << outfile <<endl;
                ////chan->cwrite(buf, to_alloc);
                chan_vector.at(j)->cwrite(buf, to_alloc);
                ////chan->cread(recv_buffer, MAX_MESSAGE);
                chan_vector.at(j)->cread(recv_buffer, MAX_MESSAGE);
                fwrite(recv_buffer, 1, fm->length, outfile);
                rem -= fm->length;
                fm->offset += fm->length;
                //cout << fm->offset << endl;
            }
            gettimeofday(&end1,NULL); //https://www.geeksforgeeks.org/measure-execution-
            double time_taken1;

            time_taken1 = (end1.tv_sec - start1.tv_sec) * 1e6;
            time_taken1 = (time_taken1 + (end1.tv_usec - start1.tv_usec)) * 1e-6;

            cout << "Time taken by program is : " << fixed << time_taken1 << setprecision(6);
            cout << " sec" << endl;


        }

        fclose(outfile);
        delete recv_buffer;
        delete buf;
        cout << "File transfer completed" << endl;



    }

    MESSAGE_TYPE q = QUIT_MSG;
    for ( int j = 0; j < nchannels; j++)
    {
        chan_vector.at(j)->cwrite (&q, sizeof (MESSAGE_TYPE));
        delete chan_vector.at(j);
        //cout << "Here" <<endl;
    }


    if (chan != control_chan){ // this means that the user requested a new channel, so the control_channel must be destroyed as well 
        control_chan->cwrite (&q, sizeof (MESSAGE_TYPE));
        delete control_chan;
    }
	// wait for the child process running server
    // this will allow the server to properly do clean up
    // if wait is not used, the server may sometimes crash
	wait (0);
    
}
