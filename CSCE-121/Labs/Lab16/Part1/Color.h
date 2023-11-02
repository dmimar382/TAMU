//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                      OVERLOADING OPERATOR '==' LAB                       //
//                                 Color.h                                  //
//                                                                          //
// Written By :                         Environment : Mac OS X 10.10.5      //
// Date ......: 2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1  //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#ifndef COLOR_H
#define COLOR_H

//////////////////////////////////////////////////////////////////////////////
//                                 Dependencies                             //
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>

//////////////////////////////////////////////////////////////////////////////
//                           Color Class Definition                         //
//////////////////////////////////////////////////////////////////////////////
class Color_error {};
class Color {
/* Public */
public:
    bool operator ==(const Color& c) const;
    Color& operator +=(const Color& c);
    Color();
    Color(int r, int g, int b);
    std::string to_str() const;
    bool is_valid_val(int) const;
    int get_R(void) const { return R; }
    int get_G(void) const { return G; }
    int get_B(void) const { return B; }
    void set_R(int);
    void set_G(int);
    void set_B(int);
/* Private */
private:
    int R;
    int G;
    int B;
};

//////////////////////////////////////////////////////////////////////////////
#endif