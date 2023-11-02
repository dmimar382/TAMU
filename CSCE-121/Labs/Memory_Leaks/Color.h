/*******************************************************************************
* Color.h                                                                      *
*******************************************************************************/
#ifndef COLOR
#define COLOR
#include <iostream>

class Color {
    /* Public */
public:
    Color(); // default constructor
    Color(int r, int g, int b); // default constructor overloaded
    int get_R(void) const {return R;}
    int get_G(void) const {return G;}
    int get_B(void) const {return B;}
    void set_R(int i) {R = i; }
    void set_G(int i) {G = i;}
    void set_B(int i) {B = i;}
    /* Private */
private:
    int R;
    int G;
    int B;
};
std::ostream& operator<<(std::ostream& os, Color const& c);

#endif  /* COLOR */