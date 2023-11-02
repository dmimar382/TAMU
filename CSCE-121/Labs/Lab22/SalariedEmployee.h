#ifndef SALARIEDEMPLOYEE_H
#define SALARIEDEMPLOYEE_H
#include <string>
#include "Employee.h"


class SalariedEmployee : public Employee {
protected:
	double annual_salary;
public:
	SalariedEmployee();
	SalariedEmployee(std::string name, double annual_salary);
	virtual double weekly_pay();
	std::string to_str();

};

#endif