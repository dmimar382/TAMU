/****************************************************************
The following program will ask for the user's first and last name,
birth year,and their height in feet and inches. The program will 
approximate the user's age and height in cm, as well as compute 
the user's average annual growth per year in centimeters, under 
the assumption that one’s height at birth is 51 cm. 
*****************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main(){

//asking for user input 
	cout << "First name: ";
	string first_name {};
	cin >> first_name;

	cout << "Last name: ";
	string last_name {};
	cin >> last_name;

	cout << "Birth year: ";
	int birth_year {};
	cin >> birth_year;

	cout << "Height in feet (do not include inches): ";
	int height_feet {};
	cin >> height_feet;

	cout << "Height in inches (do not include feet): ";
	int height_inches {};
	cin >> height_inches;
	cout << endl;

//declaring necessary constants and variables
	const int current_year {2019};
	const int inches_per_foot {12};
	const double cm_per_inch {2.54};
	int age {};
	double height{};
	double average_growth_per_year {};

//computations
	age = current_year - birth_year;
	height = (height_feet*inches_per_foot + height_inches)*cm_per_inch;
	average_growth_per_year = (height-51)/age;

//output

	cout << "Hello " << first_name << " " << last_name <<"."<<endl;
	cout << "You are " << age << " years old in " <<current_year<< "." <<endl;
	cout << "Your height is " << height << " cm." <<endl;
	cout << "You grew an average of " << average_growth_per_year <<" cm per year (assuming you were 51 cm at birth)." <<endl;

	return 0;
}