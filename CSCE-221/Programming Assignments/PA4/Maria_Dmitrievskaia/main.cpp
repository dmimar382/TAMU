/*
Programming assignment 4
Maria Dmitrievskaia 
user name: dmimar382
e-mail: dmimar382@tamu.edu
section: 511
*/



#include <string>
#include <regex>

#include "HashTable.hpp"
#include "CSVEditor.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    regex expr(".*,.*,(.*),(.*)");
	
    string inputPath = "./input.csv";
    string rosterPath = "./roster.csv";
    string outputPath = "./output.csv";
	
	int m = 0; 

	string Temp;
	ifstream ifs(rosterPath);
	while(getline(ifs, Temp))
	{
		m++;
	}

	if(m == 0)
	{
		return 0;
	}

	//cout << "M is: " << m <<endl;


    CSVEditor editor(inputPath, rosterPath, outputPath, expr, m);
    //cout << "Done with constructor" <<endl;
    editor.readCSVToTable();
    //cout << "Done with reading to function " <<endl;
    editor.writeCSVToFile();
	
	std::tuple<int, int, double> stats = editor.getStats();
	
	cout << "minimum chain len = " << std::get<0>(stats) << endl;
	cout << "maximum chain len = " << std::get<1>(stats) << endl;
	cout << "average chain len = " << std::get<2>(stats) << endl;
	
    return 0;    
}
