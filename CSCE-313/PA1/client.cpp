#include "common.h"
#include "FIFOreqchannel.h"
#include "fstream"
#include <bits/stdc++.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;


void wait ( int seconds )//http://www.cplusplus.com/forum/general/123529/
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}
}

int main(int argc, char *argv[]){

    int new_buff_capacity = MAX_MESSAGE;
    char * new_buff;

    int opt;
    int person;
    double time;
    int ecgno;
    bool time_flag = false;
    bool file_flag = false;
    char* filename;
    char* new_channel;
    bool new_channel_flag = false;
    bool new_buff_flag = false;



    // get input arguments from the user in the command line
    while ((opt = getopt(argc, argv, "p:t:e:f:cm:")) != -1) {
        switch(opt)
        {
            case 'p':
                person = stoi(optarg); //converts to int
                //cout << person <<endl;
                break;
            case 't':
                time = stod(optarg); //converts to double
                //cout << time <<endl;
                time_flag = true;
                break;
            case 'e':
                ecgno = stoi(optarg);
                //cout << ecgno <<endl;
                break;
            case 'f':
                filename = optarg;
                file_flag = true;
                //cout << filename <<endl;
                break;
            case 'c':
                new_channel_flag = true;
                //cout << "Here" <<endl;
                break;
            case 'm':
                new_buff_capacity = stoi(optarg);
                new_buff = optarg;
                new_buff_flag = true;
                //cout << "Goint through m flag" <<endl;
                break;
            case '?':
                cout << "Unknown flag" <<endl;
                break;
        }
    }
    int identity = fork(); //PID of the child is returned here
    //if you are a child, 0 is returned
    //cout <<identity <<endl;
    //cout << getpid() <<endl; //parent pid
    //also prints out 0 from the child

    if (identity ==0)
    {
        //child process
        if(new_buff_flag)
        {
            char* arg[] = {"./server", "-m", new_buff, NULL};
            execvp(arg[0],arg);
        }
        else
        {
            char* arg[] = {"./server", NULL};
            execvp(arg[0],arg);
        }

    }
    else
    {
        //parent process
        FIFORequestChannel chan ("control", FIFORequestChannel::CLIENT_SIDE);


        //handling the data message
        if ((time_flag == false) && (file_flag == false && new_channel_flag ==false))
        {

            //request 1000 data points and put in file
            struct timeval start, end; //counting the time taken for this funciton
            gettimeofday(&start, NULL);

            ofstream thousand_points;
            thousand_points.open("x1.csv");
            for ( double time = 0.0; time < 4; time +=0.004)
            {
                datamsg d(person, time, ecgno);//this is a request of the information from the server.
                chan.cwrite(&d, sizeof(datamsg));
                double ret;
                chan.cread(&ret, sizeof(double));
                thousand_points<<ret <<endl;
            }
            thousand_points.close();

            gettimeofday(&end, NULL); //https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/

            // Calculating total time taken by the program.
            double time_taken;

            time_taken = (end.tv_sec - start.tv_sec) * 1e6;
            time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

            cout << "Time taken by program is : " << fixed << time_taken << setprecision(6);
            cout << " sec" << endl;
        }
        //want 1 data point
        else if (time_flag == true || file_flag == false && new_channel_flag ==false)//time flag is true and we are requesting only 1 data point at a specific time
        {
            //want to access data requested
            struct timeval start2, end2;
            gettimeofday(&start2, NULL);

            datamsg d(person, time, ecgno);//this is a request of the information from the server.
            chan.cwrite(&d, sizeof(datamsg));
            double ret;
            chan.cread(&ret, sizeof(double));
            cout <<ret <<endl;

            gettimeofday(&end2, NULL); //https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/

            // Calculating total time taken by the program.
            double time_taken2;

            time_taken2 = (end2.tv_sec - start2.tv_sec) * 1e6;
            time_taken2 = (time_taken2 + (end2.tv_usec - start2.tv_usec)) * 1e-6;

            cout << "Time taken by program is : " << fixed << time_taken2 << setprecision(6);
            cout << " sec" << endl;




        }

        //HANDLING A FILE MESSAGE
        else if (file_flag == true && time_flag == false)
        {
            //cout << "We have a file" <<endl;
            filemsg f(0, 0);
            int size_total = sizeof(filemsg) + strlen(filename) + 1;// we cant append the filemesage with the filename,
            //so we need to create a buffer to hold both of those variables. In reality we need to send 1 more byte and that is the
            //null byte
            //need to create pointer to buffer of the size of everything together
            //cout << "size total" <<size_total <<endl;
            char *buf = new char[size_total];
            memcpy(buf, &f, sizeof(filemsg));
            //buffer has the file message, but we need to append the filename as well
            strcpy(buf + sizeof(filemsg), filename);

            chan.cwrite(buf, size_total);
            __int64_t fs;
            chan.cread(&fs,sizeof(__int64_t));
            //cout << "total file size: " << fs << endl;
            int num_messages = ceil (double(fs)/new_buff_capacity);
            //cout << "How many times do we need to send messages: " << num_messages  <<endl;

            //file size is less than 256
            filemsg* fm = (filemsg*) buf;
            if (num_messages == 1 )
            {
                //cout << "Inside if" <<endl;
                fm->offset = 0;
                fm->length = fs;
            }
            else
            {
                fm->length = new_buff_capacity;//want to extract the max number of bytes from the file at a time
                fm->offset = 0;
            }
            __int64_t  last_count = fs - new_buff_capacity* (num_messages-1);
            chan.cwrite(buf, size_total);
            char* ret_buf = new char[new_buff_capacity];
            chan.cread(ret_buf,new_buff_capacity);

            string outputfilepath = string("received/") + string(filename);
            FILE* fp = fopen(outputfilepath.c_str(),"wb");
            fwrite(ret_buf, 1, fm->length, fp);

            struct timeval start1, end1;
            gettimeofday(&start1, NULL);
            for (int i = 1; i < num_messages; i++)
            {
                //cout << "Inside for loop" <<endl;

                if (i == num_messages-1)
                {
                    //cout << fm->offset + new_buff_capacity <<endl;
                    //cout <<"last chunk ";
                    //cout << last_count <<endl;
                    fm->length = last_count;
                    ret_buf = new char[last_count];
                    fm->offset +=new_buff_capacity;
                    //cout << "HERE " << endl ;
                    chan.cwrite(buf, size_total);
                    chan.cread(ret_buf,new_buff_capacity);
                    fwrite(ret_buf, 1, fm->length, fp);
                }
                else
                {
                    //count += new_buff_capacity;
                    fm->offset +=new_buff_capacity;
                    //cout << "HERE " << endl ;
                    chan.cwrite(buf, size_total);
                    chan.cread(ret_buf,new_buff_capacity);
                    fwrite(ret_buf, 1, fm->length, fp);

                }
                //count += new_buff_capacity;

            }

            gettimeofday(&end1, NULL); //https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/

            // Calculating total time taken by the program.
            double time_taken;

            time_taken = (end1.tv_sec - start1.tv_sec) * 1e6;
            time_taken = (time_taken + (end1.tv_usec - start1.tv_usec)) * 1e-6;

            cout << "Time taken by program is : " << fixed << time_taken << setprecision(6);
            cout << " sec" << endl;

            delete [] ret_buf;
            delete [] buf;
        }

        //NEW CHANNEL MESSAGE
        if (new_channel_flag)
        {

            MESSAGE_TYPE new_chan = NEWCHANNEL_MSG;
            chan.cwrite(&new_chan, sizeof(MESSAGE_TYPE));
            char ret_buf [30];
            chan.cread(ret_buf, sizeof(ret_buf));
            string channel_name = ret_buf;
            cout << channel_name <<endl;

            FIFORequestChannel new_channel (channel_name, FIFORequestChannel::CLIENT_SIDE);

            datamsg d(2, 0.008, 1);//this is a request of the information from the server.
            new_channel.cwrite(&d, sizeof(datamsg));
            double ret;
            new_channel.cread(&ret, sizeof(double));
            cout <<ret <<endl;


            datamsg d1(1, 0.008, 2);//this is a request of the information from the server.
            new_channel.cwrite(&d1, sizeof(datamsg));
            double ret1;
            new_channel.cread(&ret1, sizeof(double));
            cout <<ret1 <<endl;

        }

        // Close the channel
        MESSAGE_TYPE quit = QUIT_MSG;
        chan.cwrite(&quit, sizeof(MESSAGE_TYPE));
        wait(2);
    }
    return 0;
}

//delete heap allocated stuff to avoid memory leaks(new)

