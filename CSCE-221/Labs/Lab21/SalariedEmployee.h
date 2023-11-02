#ifndef SALARIEDEMPLOYEE_H
#define SALARIEDEMPLOYEE_H
#include <string>
#include "Employee.h"


class SalariedEmployee : public Employee {
	double annual_salary;
public:
	SalariedEmployee();
	SalariedEmployee(std::string name, double annual_salary);
	double weekly_pay();
};

#endif