#include <iostream>
#include <vector>
#include <string>
#include "utilities121.h"
using namespace std;

int main ()
{

    cout << "Write code in driver.cpp to test your functions..." << endl;
    pause();
    cout<< lowChar('C') << endl;
    cout << upChar('d') << endl;
    string test = "coNvErT tO upPer and Lower";
    cout << upperStr(test) << endl;
    cout << lowerStr(test) << endl;
    cout << toStr(5) << " Is the integer" <<endl; 
    cout << toStr(4.32) << " is the double" << endl;
    
    string test2 = "This is the constant prompt for get function";
    cout << getInt(7, 12, test2);
    cout << getDouble(2.0,9.0,3, test2);

    //clearScreen();
    return 0;
}