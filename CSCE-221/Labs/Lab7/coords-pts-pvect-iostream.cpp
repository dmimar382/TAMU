#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

int main(int argv, char* argc[])
{
    if (argv != 2) {
        cerr << "Usage: ./a.out filename.dat" << endl;
        return 1;
    }
    string inputFile = argc[1];
    cout << "File with input data : " << inputFile << endl;

    ifstream ifs(inputFile);
    if (!(ifs.is_open())){
    	cout <<"file not open";
    	return 1;
    }

    int x{}, y {}; vector <int> x_val, y_val;
    char c{};

    while (ifs >> x >> c >> y){
    	x_val.push_back(x);
    	y_val.push_back(y);
    }

    double Distance {}, min {};
    int x_diff {}, y_diff {}, x_square{}, y_square {}, index {};
    vector <double> vmin {};
    vector <int> vindex {};

    for (int i {0}; i< x_val.size(); ++i){
    	for (int j {0}; j < y_val.size(); ++j){
    		if ( i == j )
    			continue;
    		x_diff = x_val.at(i) - x_val.at(j);
    		x_square = pow(x_diff,2);
    		y_diff = y_val.at(i) - y_val.at(j);
    		y_square = pow(y_diff,2);

    		Distance = sqrt(x_square + y_square);
    		 if (min ==0){
    		 	min = Distance;
    		 	index = j;
    		 }
    		if (Distance < min && i != j ){
    			min = Distance;
    			index = j;
    		}
    	}
   		vmin.push_back(min);
    	vindex.push_back(index);
    	min = 0;
    }

    // for ( int i {}; i < vmin.size(); ++i)
    // 	cout << vmin.at(i) << " ";
    // cout << endl;

    // for ( int i{}; i < vindex.size(); ++i)
    // 	cout << vindex.at(i) << " ";

    ofstream ofs("output.txt");
	
	
    for (int i {}; i < x_val.size(); ++i)
    	ofs << x_val.at(i) << "," << y_val.at(i) << "," << vindex.at(i) <<endl;

    return 0;
}