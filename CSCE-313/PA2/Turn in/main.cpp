#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <sstream>
#include<ctime>
#include <time.h>

using namespace std;

string trim(string input) {
    //cout << "Initial size: " << input.size() <<endl;
    string trimmed_input;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] != ' ')
        {
            trimmed_input.push_back(input[i]);
            if(input[i+1] == ' ')
                trimmed_input.push_back(' ');
        }

    }
    if(trimmed_input[trimmed_input.size() - 1] == ' ')
        trimmed_input.erase(trimmed_input.size() - 1);
    //cout << "final size: " << trimmed_input.size() <<endl;
    return trimmed_input;
}

char** vec_to_char_array(vector<string>& parts)
{
	char** result = new char* [parts.size() +1];//adds one because of NULL
	for (int i = 0; i < parts.size(); i++)
	{
		result[i] = (char*) parts[i].c_str();
	}

	result [parts.size()] = NULL;
	return result;
}

int count_num_quotes(string line, char separator1 = '\'', char separator2 = '\"' )
{
    int count =0;
    for(auto i = 0; i < line.size(); i++)
    {
        if(line[i] == separator1 || line[i] == separator2)
            count++;
    }
    cout << count <<endl;
    return count;
}

vector<string> split(string line, char separator = ' ')
{
    vector<string> separated_input;
    int c = 0;
    int num_quotes = 0; //= count_num_quotes(line);
    bool inside_quotes = false;
    int start = 0;

    for(auto i = 0; i < line.size(); i++)
    {

        if (separator == ' ' && (line[i] == '\'' || line[i] == '\"'))
        {
            //cout  << "here" <<endl;//echo "Hello | blah "
            ++num_quotes;
            string word;
            if (num_quotes %2 !=0)
            {
                inside_quotes = true;
                start = i+1;
            }
            else //quote finished
            {
                inside_quotes = false;
                for (int j = start; j < i; j++)
                    word.push_back(line[j]);
                separated_input.push_back(word);
            }
        }
       else if (inside_quotes == false)
        {
            if((line[i] == separator) || (i == (line.size()-1)))
            {
                string words ;
                if (i == line.size() - 1)
                {
                    for (int j = c; j < i + 1; j++)
                        words.push_back(line[j]);
                }
                else
                {
                    for (int j = c; j < i; j++)
                        words.push_back(line[j]);
                }
                separated_input.push_back(words);
                c = i + 1;
            }

        }
    }
    return separated_input;
}

char* gettime() //http://www.cplusplus.com/reference/ctime/ctime/
{
    time_t rawtime;
    time (&rawtime);
    return ctime (&rawtime);
}

int main()
{
	vector <int> bgs; //list of background processes
	int keyboard = dup(0);//copying standard input of the keyboard so that when we are redirecting, we wait for keyboard input
	int stdout = dup(1);//copying standard output

    char buff[1000];;
	string current_dir = getcwd(buff,sizeof(buff));
    chdir("..");
    string previous_dir = getcwd(buff,sizeof(buff));
    chdir(current_dir.c_str());

	while (true)
	{
		for(int i = 0; i < bgs.size(); i++)
		{
			if(waitpid(bgs[i],0,WNOHANG) == bgs[i])//have to call this in an asyncronus manner
			{ 
				cout << "Process: " <<bgs[i] << " ended" <<endl;
				//remove process from list
				bgs.erase(bgs.begin() +i);
				i--; //keeping i at the same exact spot
			}
		}

		//copy the keyboard and terminal value to 0 index of descriptor table
		dup2(keyboard,0);
		dup2(stdout,1);

		//char* name = getlogin_r(3);
		cout << "osboxes " << gettime(); //print a prompt
		string inputline;
		getline (cin, inputline); //get a line from standard input

		if(inputline == string("exit"))
		{
			cout << "Bye!! End of Shell " <<endl;
			break;
		}

		//check for background processes
		bool bg = false;
		inputline = trim(inputline);//gets rid of leading and trailing spaces
		//cout << "Input line : " <<inputline  <<"blaah" <<endl;
		if(inputline[inputline.size()-1] =='&')
		{
			cout << "Background process found" <<endl;
			bg = true;
			inputline = trim(inputline.substr(0,inputline.size()-1));//removes & + the space from the end of the string
		}

		vector<string> pparts = split(inputline, '|');
//		for (auto i:pparts)
//        {
//		    cout << "PPARTS " <<i <<endl;
//        }


		for( int i = 0; i < pparts.size();i++)
        {
		    int fds[2];
		    pipe(fds);
            inputline = trim(pparts[i]);

		    int pid = fork();

            if (pid == 0) //child process
            {
                //cd stuff

                if(trim(inputline).find("cd") ==0)
                {
                    current_dir = getcwd(buff,sizeof(buff));
                   // cout << trim(inputline).find("-");
                    if (trim(inputline).find("-") == 3) {
                        //string dirname = trim(split(inputline)[1]);
                        chdir(previous_dir.c_str());
                        previous_dir = current_dir;
                    }
                    else
                    {
                        string dirname = trim(split(inputline)[1]);
                        chdir(dirname.c_str());
                        previous_dir = current_dir;
                    }
                    continue;
                }



                //do the IO redirection HERE -> open the file then call dup2
                int pos = inputline.find('>');
                if (pos >= 0)
                {
                    string command = trim(inputline.substr(0,pos)); //ls
                    string filename = trim(inputline.substr(pos+1));//filename
                    inputline = command;
                    int fd = open(filename.c_str(), O_WRONLY|O_CREAT,S_IWUSR|S_IRUSR);
                    dup2(fd,1);
                    close(fd);
                }

                pos =inputline.find('<');
                if (pos >= 0)
                {
                    string command = trim(inputline.substr(0,pos)); //ls
                    string filename = trim(inputline.substr(pos+1));//filename
                    inputline = command;
                    int fd = open(filename.c_str(), O_RDONLY,S_IWUSR|S_IRUSR);
                    dup2(fd,0);
                    close(fd);
                }


                if( i < pparts.size() - 1)
                {
                    dup2(fds[1] , 1);
                    close(fds[1]);
                    //cout <<inputline <<endl;
                }
               // inputline = pparts.at(i);

                vector <string> parts = split(inputline);
                char** args = vec_to_char_array (parts);
                execvp(args[0],args);

            }
            else
            {
//			//pipe between two processes
//			char buf [100];
//			read (fds[0],buf, 100);
//			printf("PARENT: Recv %s\n", buf);

                if(bg == false)
                {
                    if (i == pparts.size()-1)
                    {
                        waitpid(pid,0,0);

                    }
                    //waitpid(pid,0,0); //parent waits for child process
                }
                else
                {
                    bgs.push_back(pid); //we do not loose track of the background processes
                    //cout << "Here" <<endl;
                }

                dup2(fds[0],0);
                close(fds[1]); //fd[1] MUST be closed, otherwise the next level will wait
            }
		}
	}
	return 0;
}
