#include <iostream>
#include "Employee.h"
#include "SalariedEmployee.h"
#include "HourlyEmployee.h"
#include "Manager.h"

using namespace std;

int main() 
{
	SalariedEmployee* emp;
	SalariedEmployee salaried("Niels Bohr", 140000);
	Manager manager("Marie Curie", 140000, 500);

	emp = &salaried;
	cout << "Salaried weekly pay: " << emp->weekly_pay() << endl;
	emp = &manager;
	cout << "Manager weekly pay: " << emp->weekly_pay() << endl;


	return 0;
}

