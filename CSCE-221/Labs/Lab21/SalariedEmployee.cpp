#include <iostream>
#include "SalariedEmployee.h"
#include <string>

using namespace std;

SalariedEmployee:: SalariedEmployee(): Employee(), annual_salary(0.0) {}
SalariedEmployee:: SalariedEmployee(std::string name, double annual_salary) : Employee(name), annual_salary(annual_salary) {}
double SalariedEmployee::weekly_pay()
{
	return annual_salary/52;

}