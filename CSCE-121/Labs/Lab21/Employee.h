#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

class Employee {

	std::string name;
public:
	Employee();
	Employee(std::string);
	void set_name(std::string);
	std::string get_name();
};
#endif