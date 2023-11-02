#include <iostream>
#include "Manager.h"
#include <string>

using namespace std;

Manager:: Manager(): SalariedEmployee(), weekly_bonus(0.0) {}
Manager:: Manager(std::string name, double annual_salary, double weekly_bonus) : SalariedEmployee(name, annual_salary), weekly_bonus(weekly_bonus){}
double Manager::weekly_pay()
{
	return SalariedEmployee::weekly_pay() + weekly_bonus;
}
std::string Manager:: to_str()
{
	stringstream ss;

	ss << "Employee's Name: " << get_name() << '\n';
	ss << "Weekly Pay: " << weekly_pay() << '\n';
	ss << "Weekly Bonus: " << weekly_bonus << '\n';
	ss << "Annual Salary: " << annual_salary << '\n';

	return ss.str();


}