#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main(){

	cout << "Enter a decimal value: " << endl;
	int value {};
	cin >> value;

	int base {};
	vector <int> remainders;

	do {
		cout << "Enter a base(2-16): " << endl;
		cin >> base;
	}
	while ( base < 2 || base > 16);

	do{
		remainder = value % base;
		remainders.push_back(remainder);
		value/=base;
	}
	while( value > 0);

	for( int i{}; i < remainders.size(); ++i)
		cout << remainders.at(i) << " ";
//     cout << "\nBase-10 value : " << dval << endl;

//     // (3) perform conversion and store results
//     // ... while some condition (remember, we continue to take mod base and subsequently divide dval by base until we reach zero...)


//     // (5) Insert value of result into output stream
//     // ex., Want output to be if converting 4 to base-2
//     // "Base-2 value : 100"
//     cout << "Base-" << base << " value : ";

//     // (5b) Print number of digits required
//     cout << "Digits required : ";


//     return 0;
// }

// char digit_to_char(int i)
// {
//     stringstream ss;
//     ss << i; char c; ss >> c;
//     return c;
// }
	return 0;
}