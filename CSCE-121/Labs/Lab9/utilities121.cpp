//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                              UTILITIES 121                               //
//                             utilities121.cpp                             //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                #includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "utilities121.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <random>

using namespace std;
//////////////////////////////////////////////////////////////////////////////
//                           Function Definitions                           //
//////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
*                              void pause(void)                              *
*                                                                            *
*       Description ....: Delay the system so that the user can read what    *
*                         is written to standard output.                     *
*                                                                            *
*                                                                            *
* Written By : Michael R. Nowak         Environment : Mac OS X 10.10.5       *
* Date ......: 2017/10/01               Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
void pause(void)
{
    std::string temp;
    std::cout << std::endl << "[Press RETURN to continue]" << std::endl;
    std::getline(std::cin, temp);
}

/*****************************************************************************
*                            char upChar(char c)                             *
*                                                                            *
*       Description ....: Converts an uppercase character to a lower case                                                   *
*        character. If a non-character is inputted, that input is returned                                                                    *
*         the user                                                                   *
* Written By :   Maria Dmitrievskaia    Environment :  Windows 10                      *
* Date ......:  02/19/19                Compiler ...:  Putty                      *
*****************************************************************************/
char upChar(char c)
{
	if (c >= 97 && c <= 122)
		c-=32;
	return c;
}

/*****************************************************************************
*                            char lowChar(char c)                            *
*                                                                            *
*       Description ....: Converts a lowercase character to an upper case                                                   *
*       character. If a non-character is inputted, that input is returned                                                                    *
*       the upper                                                            *
*                                                                            *
*                                                                            *
* Written By : Maria Dmitrievskaia      Environment : Windows 10             *
* Date ......: 02/19/19                 Compiler ...: Putty                  *
*****************************************************************************/
char lowChar(char c)
{
	if (c >=65 && c <=90)
		c+=32;

	return c;
}

/*****************************************************************************
*                    std::string upperStr(std::string s)                     *
*                                                                            *
*       Description ....: Converts a string of characters to a string
		containing only uppercase characters.                                                    *
*                                                                            *
*                                                                            *
* Written By :  Maria Dmitrievskaia     Environment :   Windows 10           *
* Date ......:   02/19/02               Compiler ...:   Putty                *
*****************************************************************************/
string upperStr(string const& Input)
{
	string upper = "";
	for(int i = 0; i < Input.size();++i){
		upper += upChar(Input[i]);
	}
	return upper;
}

/*****************************************************************************
*                    std::string lowerStr(std::string s)                     *
*                                                                            *
*       Description ....:  Converts a string of characters to a string                            *
*         containing only lowercase characters.                                                                    *
*                                                                            *
* Written By : Maria Dmitrievskaia      Environment :  Windows 10            *
* Date ......: 02/19/19                 Compiler ...:  Putty                  *
*****************************************************************************/
string lowerStr(string const& Input)
{
	string lower = "";
	for(int i = 0; i < Input.size();++i){
		lower += lowChar(Input[i]);
	}
	return lower;
}

/*****************************************************************************
*                         std::string to_str(int i)                          *
*                                                                            *
*       Description ....:  The function creates a string containing a passed *
		integer value.                                                        *
*                                                                            *
* Written By : Wesley Myers             Environment : Windows 10             *
* Date ......: 02/19/19                 Compiler ...: Putty                  *
*****************************************************************************/
string toStr(int i)
{
	stringstream ss; 
	ss << i; 
	string s = ss.str();
	return s;
}

/*****************************************************************************
*                        std::string to_str(double d)                        *
*                                                                            *
*       Description ....:  The function creates a string containing a passed *
		floating point value.                                                       *                                                   *
*                                                                            *
*                                                                            *
* Written By : Wesley Myers             Environment : Windows 10             *
* Date ......: 02/19/19                  Compiler ...: Putty                 *
*****************************************************************************/
string toStr(double i) 
{ 
	stringstream ss; 
	ss << i; 
	string s = ss.str(); 
	return s;
}

/*****************************************************************************
*          int getInt(int low, int high, std::string const& prompt)          *
*                                                                            *
*       Description ....: Asks user to input a number between passed high and
*		low values. 
*                                                                            *
*                                                                            *
* Written By : Wesley and Maria         Environment : Windows 10               *
* Date ......: 02/19/19                  Compiler ...: Putty                 *
*****************************************************************************/
int getInt(int low, int high, std::string const& prompt) 
{ 
	cout << prompt; 
	cout << "Enter an integer value between " << low << " and  " << high << endl;
	int input; 
	do 
	{
		cin >> input; 
		if (cin.bad())  
		{
			throw runtime_error("stream corrupted"); 
			break;
		} 
		if (cin.fail()) 
		{
			
			cout << "Input you have provided is invalid..." << endl << "Please try again:" << endl;
			cin.clear();
			cin.ignore(numeric_limits <streamsize>::max ( ) , '\n');
			cin >>input;
		} 
		if (cin.eof()) {
			throw runtime_error("unexpected eof");
			break;  
		} 

		if (input <= low || input >= high) 
		{
			cout << "Input not in range...\nplease try again" << endl;
		}

	} while (!cin.good() || (input <= low || input >= high));
	
	return input;
}

/*****************************************************************************
*            double getDouble(double low, double high, double tolerance,     *
*                                     		  std::string const& prompt)     *
*                                                                            *
*       Description ....:                                                    *
*                                                                            *
*                                                                            *
* Written By :  Maria and Wesley     Environment :  Windows 10                      *
* Date ......:  02/19/19                Compiler ...:   Putty                *
*****************************************************************************/
double getDouble(double low, double high, double tolerance, std::string const& prompt) 
{ 
	cout << prompt; 
	cout << "Enter a double value between " << low << " and  " << high << endl;
	double input; 
	double lower_low = low-tolerance;
	double higher_high = high + tolerance;
	do 
	{
		cin >> input; 
		if (cin.bad())  
		{
			throw runtime_error("stream corrupted"); 
			break;
		} 
		if (cin.fail()) 
		{
			cout << "Input you have provided is invalid..." << endl << "Please try again:" << endl;
			cin.clear();
			cin.ignore(numeric_limits <streamsize>::max ( ) , '\n ');
			cin >> input;
		} 
		if (cin.eof()) {
			throw runtime_error("unexpected eof");
			break;  
		} 

		if ((input <= (lower_low) )|| (input >= (higher_high)))
		{
			cout << "Input not in range...\nplease try again" << endl;
		}

	} while (!cin.good() || ((input <= lower_low) || (input >= higher_high)));
	
	return input;
}


/*****************************************************************************
*                           void clearScreen(void)                           *
*                                                                            *
*       Description ....: This function clears the contents of the terminal  *
*          window                                                                  *
*                                                                            *
* Written By :  Maria Dmitrievskaia    Environment :  Window 10                      *
* Date ......:   02/19/19              Compiler ...:  Putty                 *
*****************************************************************************/
void clearScreen(void)
{
	system("clear");
}