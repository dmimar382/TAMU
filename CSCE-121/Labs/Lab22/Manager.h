#ifndef MANAGER_H
#define MANAGER_H
#include <string>
#include "Employee.h"
#include "SalariedEmployee.h"
#include <sstream>


class Manager : public SalariedEmployee {
	double weekly_bonus;
public:
	Manager();
	Manager(std::string name, double annual_salary, double weekly_bonus);
	double weekly_pay();
	std::string to_str();
};

#endif