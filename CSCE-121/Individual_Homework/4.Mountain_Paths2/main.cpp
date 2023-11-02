#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <cmath>
#include "functions.h"


using namespace std;

int main (){
	string fname {};
	int noRows{}, noCols{};
	vector<vector<int>> vect_1 {};
	cin >> noRows >> noCols >> fname;
	//Validate if the input is correct
	if(cin.fail()){
		cout << "Error: input not valid ";
		return 1;
	}

	ifstream ifs{fname};
	if(!ifs.is_open()){
		cout << "Error: ";
		return 1;
	}
	

	//Reads data into a 2D vector:
	for( int i {}; i < noRows; ++i)
	{
		vector <int> vect_2 {};
		for(int j {}; j < noCols; ++j)
		{
			if (ifs.eof())
			{
				break;
			}
			int read {};
			ifs >> read;
			if (ifs.fail())
			{
				cout << "Error: characters in data";
				return 1;
			}
			else
			{
				vect_2.push_back(read);
			}
		}
		vect_1.push_back(vect_2);

		if (ifs.eof ())
		{
			cout << "Error: too few data";
			break;
		}
	}

	int garbage{};
	ifs >>garbage;

	if(!(ifs.fail()))
	{
		cout << "Error: too much data" << endl;
		return 1;
	}

	else if(ifs.bad())
	{
		cout << "Error: ";	
		return 1;
	} 

	else if (ifs.fail())
	{
		ifs.clear();
		ifs.ignore(numeric_limits <streamsize>::max(),'\n');
	}

//Calculating the maximum and minimum values:
	double min {};
	double max {};

	for(int i{}; i< noRows; ++i)
	{
		for (int j {}; j < noCols; ++j)
		{

			if (i == 0 && j == 0)
			{
				min = vect_1.at(i).at(j);
				max = vect_1.at(i).at(j);
			}
			if (vect_1.at(i).at(j) < min)
			{
				min = vect_1.at(i).at(j);
			}
			if (vect_1.at(i).at(j) > max)
			{
				max = vect_1.at(i).at(j);
			}
		}
	}

//Calculating the shade of grey for each point:
	vector<vector<int>> R_val {}, G_val {}, B_val{};
	double gray_shade {};

	for(int i{}; i< noRows; ++i)
	{
		vector <int> gray_shades {};
		for (int j {}; j < noCols; ++j)
		{
			gray_shade = round(255*(vect_1.at(i).at(j) - min) / (max - min) );
			//cout << gray_shade << " "<< endl;
			gray_shades.push_back(gray_shade);
		}
		R_val.push_back(gray_shades);
		G_val.push_back(gray_shades);
		B_val.push_back(gray_shades);
	}


	// cout << "The R G B values are as follows:" << endl;
	// for (int i {}; i < noRows; ++i)
	// 	for (int j {}; j < noCols; ++j)
	// 		cout << R_val.at(i).at(j) << " " << G_val.at(i).at(j) << " "<< B_val.at(i).at(j) << " " << endl;


	//Part 2:
	int minimum = numeric_limits<int>::max();
	int min_row = 0;

	for ( int Row = 0; Row < noRows; Row++)
	{
		int Distance = colorPath(vect_1, R_val, G_val, B_val, 252, 25, 63, Row); //(vect_1.size()/2)

		if (Distance < minimum)
		{
			minimum = Distance;
			min_row = Row;
		}
		else
			minimum = minimum;
	}  

	// cout << endl << "The R G B values after first function call are as follows:" << endl;
	// for (int i {}; i < noRows; ++i)
	// 	for (int j {}; j < noCols; ++j)
	// 		cout << R_val.at(i).at(j) << " " << G_val.at(i).at(j) << " "<< B_val.at(i).at(j) << " " << endl;

	// cout <<endl;

//Call function again and color the path of least resistance in green 
	colorPath(vect_1, R_val, G_val, B_val, 31, 253, 13, min_row);


	// cout << endl << "The R G B values after second function call are as follows:" << endl;
	// for (int i {}; i < noRows; ++i)
	// 	for (int j {}; j < noCols; ++j)
	// 		cout << R_val.at(i).at(j) << " " << G_val.at(i).at(j) << " "<< B_val.at(i).at(j) << " " << endl;

	cout <<endl;

//Creating a ppm file:
	const int max_color_val {255};
	ofstream ofs(fname + ".ppm");

	ofs << "P3" <<endl;
	ofs << noCols << " " << noRows << endl;
	ofs << max_color_val <<endl;

	for(int i{}; i< noRows; ++i)
	{
		for (int j {}; j < noCols; ++j)
		{
			ofs << R_val.at(i).at(j) << " " << G_val.at(i).at(j)<< " " << B_val.at(i).at(j) << " " <<endl;
		}
	}
	ofs << endl;

	// for(int i{}; i< noRows; ++i){
	// 	for (int j {}; j < noCols; ++j){
	// 		cout<< R_val.at(i).at(j) << " " << G_val.at(i).at(j)<< " " << B_val.at(i).at(j) << " " <<endl;
	// 	}
	// }

	return 0;
}
