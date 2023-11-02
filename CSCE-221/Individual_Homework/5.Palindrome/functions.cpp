#include <iostream>
#include <string>
#include "functions.h"

using namespace std;


void printUsageInfo(string s)
{
	cout << "Usage: "<< s <<" [-c] [-s] string ...\n  -c: turn on case sensitivity\n  -s: turn off ignoring spaces\n";
}

bool isPalindrome (string user_string, bool c_flag, bool s_flag)
{
	//Step 1:
	//ignore punction ALWAYS -> get rid of it
	string no_punct;

	for (int i = 0; i < user_string.length(); ++i)
		if ((user_string[i] >= 65 && user_string[i] <=90) ||(user_string[i] >=97 && user_string[i] <= 122) || (user_string[i] == 32))
			no_punct += user_string[i];

	//for (int i = 0; i < user_input.length(); ++i){
	// cout << new_string[i];
	//}
	//s=false we not erasing spaces
	//!c && s - no flags 
	string palin_string;

	//Step 2:
	//CASE 1 : remove capital letters and leave spaces
	if( !c_flag && !s_flag)
	{
		for (int i = 0; i < no_punct.length(); ++i)
		{
			if (no_punct[i] >= 65 && no_punct[i] <=90)
				no_punct[i] = tolower(no_punct[i]);
			palin_string += no_punct[i];
		}
	}

	//Case 3: remove capital letters and remove spaces:
	else if( !c_flag && s_flag)
	{
		for (int i = 0; i < no_punct.length(); ++i)
		{
			if (no_punct[i] >= 65 && no_punct[i] <=90)
			{
				no_punct[i] = tolower(no_punct[i]);
				//palin_string += no_punct[i];
			}

			else if (no_punct[i] == ' ')
			{
				continue;
				//no_punct[i] = 0;
				//palin_string += palin_string.substr(i+1,1);
			}

			palin_string += no_punct[i];
			//cout << palin_string[i];
		}
		//cout << endl;
	}
	//Case 2: consider capital letters and leave spaces:
	else if(c_flag && !s_flag)
	{
		palin_string = no_punct;
	}

	//case 4: consider capital letters and remove spaces
	else if (c_flag && s_flag)
	{
		for (int i = 0; i < no_punct.length(); ++i)
		{
			if (no_punct[i] == ' ')
				continue;
			palin_string += no_punct[i];
		}
	}

	return isPalindromeR(palin_string);
}

bool isPalindromeR(string palin_string)
{
	int len = palin_string.length();
 	
 	if (len <= 1)
 		return true;
	else if (palin_string.at(0) == palin_string.at(len-1))
	{
		string new_string = palin_string.substr(1, len - 2);
		return isPalindromeR(new_string);
	}
	else
		return false;
} 

