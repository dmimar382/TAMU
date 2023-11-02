#include <iostream>
#include <string>
#include "functions.h"

using namespace std;

int main(int argc, char* argv[])
{
	string prog_name = argv[0];
	if ( argc < 2)
	{
		printUsageInfo(prog_name);
		//cout << "First case";
		return 1;
	}
	//Checking if we have a flag
	bool is_flag = false, c_flag = false, s_flag = true;
	int num_flags = 0;
	for (int i = 1; i < argc; ++i)
	{ 	bool invalid_flag=false;
		if (argv[i][0] == '-')
		{
			is_flag = true;
			++num_flags; 
		}
		else
			is_flag = false;

		if (is_flag)
		{
			//Checking if we have a C flag:
			string arg = argv[i];
			for (int j =0; j < arg.size(); ++j)
			{
				if ((arg[j] == 'c') || (arg[j] == 'C'))
				{
					c_flag = true; //means consider capital letters
					invalid_flag=false;
				} 
				//cout << "Is there a C flag?" <<c_flag<<endl;
				else if ((arg[j] == 's') || (arg[j] == 'S'))
				{
					s_flag = false;// means consider having spaces
					invalid_flag=false;
				}
				//cout << "Is there a S flag?" << s_flag <<endl; 
				else
				{
					invalid_flag = true;
				}
			}
			
		}
		if (is_flag && ((!c_flag && s_flag && invalid_flag) || argc<=2))
		{
			printUsageInfo(argv[0]);
			//cout << "Second case";
			return 1;
		} 
	} 
	//Calling isPalindrome for each inputted string:
	for (int k = num_flags + 1; k < argc; k++)
	{
		//cout << "argv[k] " << argv[k] <<endl;
		if (isPalindrome(argv[k], c_flag, s_flag))
			cout << "\"" << argv[k] << "\"" << " is a palindrome." <<endl;
		else
			cout << "\"" << argv[k] << "\"" << " is not a palindrome." <<endl;
	}

	return 0;
}