//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                     CLASS ATTRIBUTES LAB : SET ONCE                      //
//                               Student.cpp                                //
//                                                                          //
// Written By :                         Environment : Mac OS X 10.10.5      //
// Date ......: 2017/06/29              Compiler ...: Homebrew GCC 6.3.0_1  //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#include "Student.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                   Student Class Member Definitions                       //
//////////////////////////////////////////////////////////////////////////////

// parameterized contructor definition
Student::Student(string name, int uin) : name{name}, uin{uin}
{
    // this->uin = uin;
}

// parameterized constructor without name
Student::Student(int uin) : name{""}, uin{uin}

{
    // this->uin = uin;
}

//mutators and accessors
string Student::getName() const
{
    return name;
}
void Student::setName(string name)
{
    this->name = name;
}

int Student::getUIN() const
{
    return uin;
}

// void Student::setUIN(int uin)
// {
// //     this->uin = uin;
// // }

string Student::to_str() const
{
    stringstream ss;
    ss << "Name: " << name << endl;
    ss << "UIN: " << uin << endl;
    return ss.str();
}