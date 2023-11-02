#ifndef HOURLYEMPLOYEE_H
#define HOURLYEMPLOYEE_H
#include <string>
#include "Employee.h"


class HourlyEmployee : public Employee {
	double hourly_wage;
	double hours_worked;
public:
	HourlyEmployee();
	HourlyEmployee(std::string name, double hourly_wage);
	void set_hours_worked(double);
	double get_hours_worked();
	double weekly_pay();
};

#endif