#include "TemperatureDatabase.h"
#include "LinkedList.h"
#include <fstream>
#include <sstream>
using namespace std;

// Default constructor/destructor. Modify them if you need to.
TemperatureDatabase::TemperatureDatabase() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	// Implement this function for part 1

	const int current_year = 2019;
	ifstream ifs{filename};
	if (!ifs.is_open())
	{
		cout << "Error: Unable to open input.dat ";
		return;
	}

	
	while(!ifs.eof())
	{

		string id;
		int year = 1800;
		int month = 0;
		double temperature = 0.0;

		string line=" ";
		getline(ifs,line);
		if( line =="")
			continue;
		stringstream ss;
		ss << line;
		ss >> id >> year >> month >> temperature;
		
		if(ss.fail())
		{
			cout << "Error: Other invalid input\n";
			continue;
		}

		if(month < 1 || month > 12)
		{
			cout << "Error: Invalid month " << month << '\n';
			continue;
		} 
		if(year > current_year || year < 1800)
		{
			cout << "Error: Invalid year " << year <<'\n';
			continue;
		}
		if(temperature == -99.99)
			continue;
		if ((temperature < -50.0) || (temperature > 50.0))
		{
			cout << "Error: Invalid temperature " << temperature << '\n';
			continue;
		}
		records.insert(id,year,month, temperature);
	}
}

void TemperatureDatabase::performQuery(const string& filename) {
	// Implement this function for part 2
	//  Leave it blank for part 1
}
