//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                      OVERLOADING OPERATOR '<<' LAB                       //
//                                Color.cpp                                 //
//                                                                          //
// Written By :                         Environment : Mac OS X 10.10.5      //
// Date ......: 2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1  //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "Color.h"

//////////////////////////////////////////////////////////////////////////////
//                     Color Class Member Definitions                       //
//////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
*                               Color::Color()                               *
*                                                                            *
*   Description ....: Defualt constructor for Color class                    *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.10.5       *
* Date ......:  2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
Color::Color() : R(255), G(255), B(255)
{

}

/*****************************************************************************
*                     Color::Color(int r, int g, int b)                      *
*                                                                            *
*   Description ....: Parameterized constructor for Color class              *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.10.5       *
* Date ......:  2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
Color::Color(int r, int g, int b): R(r), G(g), B(b)
{
    if (!is_valid_val(R) || !is_valid_val(G) || !is_valid_val(B)) {
        throw Color_error{};
    }
}

/*****************************************************************************
*                     std::string Color::to_str() const                      *
*                                                                            *
*   Description ....: Creates string "(R,G,B)", where R, G, and B are        *
*                     the values stored in a respective object of the class  *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.10.5       *
* Date ......:  2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
std::string Color::to_str() const
{
    std::stringstream ss;
    ss << '(' << R << ',' << G << ',' << B << ')';
    return ss.str();
}

/*****************************************************************************
*                   bool Color::is_valid_val(int v) const                    *
*                                                                            *
*   Description ....: Checks whether the actual argument provided to the     *
*                     parameter v constitutes a valid color value            *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.10.5       *
* Date ......:  2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
bool Color::is_valid_val(int v) const
{
    if (v < 0 || v > 255)
        return false;
    else
        return true;
}

/*****************************************************************************
*                          void Color::set_R(int r)                          *
*                                                                            *
*   Description ....: Sets the member R to the actual argument provided      *
*                     to the parameter, provided that that argument is a     *
*                     valid color value.  If it is not, the function         *
*                     throws Color_error{}                                   *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.10.5       *
* Date ......:  2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
void Color::set_R(int r)
{
    if (!is_valid_val(r))
        throw Color_error{};
    R = r;
}

/*****************************************************************************
*                          void Color::set_G(int g)                          *
*                                                                            *
*   Description ....: Sets the member G to the actual argument provided      *
*                     to the parameter, provided that that argument is a     *
*                     valid color value.  If it is not, the function         *
*                     throws Color_error{}                                   *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.10.5       *
* Date ......:  2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
void Color::set_G(int g)
{
    if (!is_valid_val(g))
        throw Color_error{};
    G = g;
}

/*****************************************************************************
*                          void Color::set_B(int B)                          *
*                                                                            *
*   Description ....: Sets the member B to the actual argument provided      *
*                     to the parameter, provided that that argument is a     *
*                     valid color value.  If it is not, the function         *
*                     throws Color_error{}                                   *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.10.5       *
* Date ......:  2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
void Color::set_B(int b)
{
    if (!is_valid_val(b))
        throw Color_error{};
    B = b;
}

//////////////////////////////////////////////////////////////////////////////
//                       Helper Function Definitions                        //
//////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
*         std::ostream& operator<<(std::ostream& os, const Color& c)         *
*                                                                            *
*   Description ....:                                                        *
*                                                                            *
* Written By :                          Environment : Mac OS X 10.10.5       *
* Date ......:  2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1   *
*****************************************************************************/
std::ostream& operator<<(std::ostream& os, const Color& c)
{
    os << c.to_str();
    return os;

}
//////////////////////////////////////////////////////////////////////////////