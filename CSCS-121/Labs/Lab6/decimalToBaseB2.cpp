//The following code converts a decimal value to a base of the users choosing


#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

char digit_to_char(int);

int main (int argc, char *argv[]){

	cout << "Enter a decimal value: ";
	int value {};
	cin >> value;

	int base_value {};
    int remainder {};
	vector <int> remainders;

	do {
		cout << "Enter a base(2-16): ";
		cin >> base_value;}
	while ( base_value <2 || base_value > 16);

	do{
		remainder = value % base_value;
		remainders.push_back(remainder);
		value/=base_value;}
	while( value > 0);
    
    cout << "Base-" << base_value << " value : ";

    int a {};
    a = remainders.size()-1;
	if (remainders.size() == 0)
        cout << '0';
    else{
        for( auto i{a}; i>=0; i--)
		cout << remainders.at(i);}
    

     // (5b) Print number of digits required
     cout << "\nDigits required : " << remainders.size() <<endl;
     return 0;
 }

 char digit_to_char(int i)
 {
     stringstream ss;
     ss << i; char c; ss >> c;
     return c;
 }
