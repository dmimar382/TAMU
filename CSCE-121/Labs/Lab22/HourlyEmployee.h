#ifndef HOURLYEMPLOYEE_H
#define HOURLYEMPLOYEE_H
#include <string>
#include "Employee.h"


class HourlyEmployee : public Employee {
	double hourly_wage;
	double hours_worked;
public:
	HourlyEmployee();
	HourlyEmployee(std::string name, double hourly_wage, double hours_worked = 0.0);
	void set_hours_worked(double);
	double get_hours_worked() const;
	double weekly_pay();
	std::string to_str();
};

#endif