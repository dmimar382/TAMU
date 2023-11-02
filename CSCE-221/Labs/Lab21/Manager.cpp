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