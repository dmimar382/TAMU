#include <iostream>

using namespace std;

int main () {

	const int inches_per_foot {12};
	const int feet_per_yard {3};
	const int inches_per_yard {36};
	int number_yards {};
	int inches_left {};
	int feet {};
	int inches_left_again;
	int inches {};

	cout << "Input number of inches: " <<endl;
	int number_inches {};
	cin >>number_inches;

	number_yards = number_inches / inches_per_yard;
	inches_left =  number_inches - number_yards*inches_per_yard;

	feet = inches_left / inches_per_foot;
	inches_left_again = inches_left - feet*inches_per_foot;

	inches = inches_left_again;

	cout << number_inches << " = " << number_yards << " yards, " << feet << " feet, " << inches << " inches. " <<endl;







	return 0;
}