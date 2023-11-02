#include <iostream>
#include <string>

using namespace std;

int main (){
	// string  fname = "Michael";
	// string lname = "Nowak";

	// cout << "Hello, " << fname << " " << lname << "!" <<endl;

	string fname = " ";
	string lname = " ";
	cout << "Please enter your first name [space] last name: " <<endl;

	cin >> fname >> lname;

	cout << "Hello, " << fname << " " << lname << "!" <<endl;
	
	return 0; 
}