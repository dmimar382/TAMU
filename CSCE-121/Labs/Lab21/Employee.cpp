#include <iostream>
#include "Employee.h"
#include <string>

using namespace std;

Employee::Employee() {}
Employee::Employee(string name):name(name) {}

void Employee::set_name(string Name)
{
	name = Name;
}

string Employee::get_name()
{
	return name;
}