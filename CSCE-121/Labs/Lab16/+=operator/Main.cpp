//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                      OVERLOADING OPERATOR '+=' LAB                       //
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

    Color color2(255,255,255);
    cout << "Color color2 : " << color2.to_str() << endl;
    cout << "after color2+=color : " << endl;
    color2+=color;
    cout << "\tColor color : " << color.to_str() << endl;
    cout << "\tColor color2 : " << color2.to_str() << endl;

    Color color3(167,190,190);
    cout << "Color color3 : " << color3.to_str() << endl;
    cout << "after color3+=color : " << endl;
    color3+=color;
    cout << "\tColor color : " << color.to_str() << endl;
    cout << "\tColor color3 : " << color3.to_str() << endl;
    

}

//////////////////////////////////////////////////////////////////////////////