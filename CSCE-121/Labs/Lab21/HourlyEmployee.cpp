#include <iostream>
#include "HourlyEmployee.h"
#include <string>

using namespace std;

HourlyEmployee::HourlyEmployee(): Employee(), hourly_wage(0.0), hours_worked(0.0) {}
HourlyEmployee::HourlyEmployee(std::string name, double hourly_wage): Employee(name), hourly_wage(hourly_wage), hours_worked(0.0) {}
void HourlyEmployee::set_hours_worked(double hours_worked)
{
	this->hours_worked = hours_worked;
}
double HourlyEmployee::get_hours_worked()
{
	return this->hours_worked;
}
double HourlyEmployee::weekly_pay()
{
	if (hours_worked < 40)
		return hours_worked * hourly_wage;
	return hours_worked * hourly_wage + (hours_worked-40) * hourly_wage * 0.5;
}