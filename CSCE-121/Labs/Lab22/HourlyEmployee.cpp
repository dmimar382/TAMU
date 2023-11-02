#include <iostream>
#include "HourlyEmployee.h"
#include <string>
#include <sstream>

using namespace std;

HourlyEmployee::HourlyEmployee(): Employee(), hourly_wage(0.0), hours_worked(0.0) {}
HourlyEmployee::HourlyEmployee(std::string name, double hourly_wage, double hours_worked): Employee(name), hourly_wage(hourly_wage), hours_worked(hours_worked) {}
void HourlyEmployee::set_hours_worked(double hours_worked)
{
	this->hours_worked = hours_worked;
}
double HourlyEmployee::get_hours_worked() const
{
	return this->hours_worked;
}
double HourlyEmployee::weekly_pay()
{
	if (hours_worked < 40)
		return hours_worked * hourly_wage;
	return hours_worked * hourly_wage + (hours_worked-40) * hourly_wage * 0.5;
}

std::string HourlyEmployee::to_str()
{	
	stringstream ss;

	ss << "Employee's Name: " << get_name() << '\n';
	ss << "Weekly Pay: " << weekly_pay() << '\n';
	ss << "Hours Worked: " << get_hours_worked() << '\n';
	ss << "Hourly Wage: " << hourly_wage << '\n';

	return ss.str();


}