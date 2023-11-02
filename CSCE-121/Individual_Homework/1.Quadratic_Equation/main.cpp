/******************************************************
The following program will solve quadratic equations
based on the coeficient values the user enters.
******************************************************/
#include <iostream>
#include <cmath>


using namespace std;

int main(){
	
//Ask user to input coefficient values
	double a {}, b {}, c{}, x{};
	cin >> a >> b >> c;

//	cout << a << " " << b <<" " << c <<endl;

//Records and outputs the quadratic equation that will be solved	
	if (b >= 0)
		cout << a << "x^2 + " << b << "x ";
	else
		cout << a << "x^2 - " << abs(b) << "x ";

	if (c >= 0)
		cout << "+ " << c << " = 0" << endl;
	else
		cout <<"- "<< abs(c) << " = 0" << endl;
		
	

// c - value doe not matter, if a and b are 0
	if ((a == 0) && (b==0)){
		cout << "Unable to determine root(s)." <<endl;
	}
// if a = 0, then we are solving a linear equation
	else if (a==0) {
		x = (0-c)/b;
		cout << "x = " << x << endl;
	}
	else {
		double discriminant {};
		discriminant = pow(b,2) - 4*a*c;
		
// 3 possible ranges of values for the determinate yeild different solutions:
		if (discriminant < 0){
			double x {}, x_imaginary {};
			x = -b/(2*a);
			x_imaginary = sqrt(abs(discriminant))/(2*a);

			if (x_imaginary < 0){
				cout << "x = " << x << " +  " << abs(x_imaginary) << "i" <<endl;
				cout << "x = " << x << " -  " << abs(x_imaginary) << "i" <<endl;
			}
			else {
				cout << "x = " << x << " - " << x_imaginary << "i" <<endl;
				cout << "x = " << x << " + " << x_imaginary << "i" <<endl;
			}
		}
		else if (discriminant == 0) {
			x = -b/(2*a);
			cout << "x = " << x << endl;
		}
		else{
			double x1 {}, x2 {}; 
			x1 = (-b - sqrt(discriminant))/(2*a);
			x2 = (-b + sqrt(discriminant))/(2*a);

			cout << "x = " << x1 << endl;
			cout << "x = " << x2 << endl;
		}
	}
	return 0;
}