//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                     CLASS ATTRIBUTES LAB : SET ONCE                      //
//                                Student.h                                 //
//                                                                          //
// Written By :                         Environment : Mac OS X 10.10.5      //
// Date ......: 2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1  //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#ifndef STUDENT_H
#define STUDENT_H

//////////////////////////////////////////////////////////////////////////////
//                                  Includes                                //
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include <sstream>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
//                         Student Class Definition                         //
//////////////////////////////////////////////////////////////////////////////

class Student {
public:
    // constructors
    Student(std::string, int);
    Student(int);

    // mutators & accessors
    std::string getName() const;  // getter for name
    void setName(std::string); // setter for name
    int getUIN() const;  // getter for UIN
    void setUIN(int); // setter for UIN
    std::string to_str() const;

private:
    std::string name;
    const int uin;
};

#endif