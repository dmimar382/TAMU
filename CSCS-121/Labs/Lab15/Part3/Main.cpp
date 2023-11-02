//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                        CLASS CONSTRUCTORS LAB                            //
//                               MAIN.CPP                                   //
//                                                                          //
//  Date ...: 18/MAR/2017                                                   //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                  Includes                                //
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <limits>
#include "Color.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                                      main                                //
//////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    string prompt = "Please enter the r, g, and b integer values of a color, \nwith each separated by a space (e.x., \"255 255 255\"): ";
    // Part 1
    Color color;
    cout << "Color values after declaration : " << color.to_str() << endl;
    char cont = 'y'; // continue is yes
    while (tolower(cont) == 'y') {
        cout << prompt;
    	int r, g, b;
        while (!(cin >> r >> g >> b)) {
            if (cin.bad() || cin.eof()) {
                return 1;
            } else if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Invalid input." << endl << endl << prompt;
        }
        try {
			color.set_R(r); color.set_G(g); color.set_B(b);
			cout << "Color : " << color.to_str() << endl << endl;
        }
        catch (Color_error& e) {
        	cout << "Invalid input." << endl << endl;
        }
        cout << "Do another? (y or Y) ";
        cin >> cont;
    }
    
    // Part 2
   //  char cont = 'y'; // continue is yes
   //  while (tolower(cont) == 'y') {
   //      cout << prompt;
   //  	int r, g, b;
   //      while (!(cin >> r >> g >> b)) {
   //          if (cin.bad() || cin.eof()) {
   //              return 1;
   //          } else if (cin.fail()) {
   //              cin.clear();
   //              cin.ignore(numeric_limits<streamsize>::max(), '\n');
   //          }
   //          cout << "Invalid input." << endl << endl << prompt;
   //      }
   //      try {
			// Color color(r, g, b);
			// cout << "Color : " << color.to_str() << endl << endl;
   //      }
   //      catch (Color_error& e) {
   //      	cout << "Invalid input." << endl << endl;
   //      }
   //      cout << "Do another? (y or Y) ";
   //      cin >> cont;
   //  }
    
    cout << "Goodbye!" << endl;
    return 0;
}
