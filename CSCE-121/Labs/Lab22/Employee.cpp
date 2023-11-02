#include <iostream>
#include "Employee.h"
#include <string>
#include <sstream>

using namespace std;

Employee::Employee() {}
Employee::Employee(string name):name(name) {}

void Employee::set_name(string Name)
{
	name = Name;
}

string Employee::get_name() const
{
	return name;
}

 ostream& Employee::operator<<(ostream& os)
 {
 	os << to_str();
 	return os;

 }