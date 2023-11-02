#include <iostream>
#include "SalariedEmployee.h"
#include <string>
#include <sstream>

using namespace std;

SalariedEmployee:: SalariedEmployee(): Employee(), annual_salary(0.0) {}
SalariedEmployee:: SalariedEmployee(std::string name, double annual_salary) : Employee(name), annual_salary(annual_salary) {}
double SalariedEmployee::weekly_pay()
{
	return annual_salary/52;

}
std::string SalariedEmployee::to_str()
{
	stringstream ss;

	ss << "Employee's Name: " << get_name() << "\n";
	ss << "Weekly Pay: " << weekly_pay() << "\n";
	ss << "Annual Salary: " << annual_salary << "\n";

	return ss.str();


}