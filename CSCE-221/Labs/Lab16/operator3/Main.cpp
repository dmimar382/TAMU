//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                      OVERLOADING OPERATOR '<<' LAB                       //
//                                 Main.cpp                                 //
//                                                                          //
// Written By :                         Environment : Mac OS X 10.10.5      //
// Date ......: 2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1  //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Color.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                                  main()                                  //
//////////////////////////////////////////////////////////////////////////////
int main()
{
    Color color(80,125,125);
    cout << "Color color : " << color.to_str() << endl;
    
    cout << "Color color : " << color << endl;
    
    return 0;
}

//////////////////////////////////////////////////////////////////////////////