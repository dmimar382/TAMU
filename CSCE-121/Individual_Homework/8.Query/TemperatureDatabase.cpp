#include "TemperatureDatabase.h"
#include "LinkedList.h"
#include "Node.h"
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
		if( line == "")
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

	ifstream ifs{filename};
	ofstream ofs("result.dat");
	
	if (!ifs.is_open())
	{
		cout << "Error: Unable to open input.dat ";
		return;
	}
	
	while(!ifs.eof())
	{
		const int current_year = 2019;
		string id;
		string operation;
		int begin_year = 1800;
		int end_year = 2019;

		string line=" ";
		getline(ifs,line);
		if( line =="")
			continue;
		stringstream ss;
		ss << line;
		ss >> id >> operation >> begin_year >> end_year;
		
		if(ss.fail())
		{
			cout << "Error: Other invalid query\n";
			continue;
		}
		if (operation != "AVG" && operation != "MODE")
		{
			cout << "Error: Unsupported query " << operation << "\n";
			continue;
		}
		if(begin_year > end_year)
		{
			cout << "Error: Invalid range " << begin_year << "-" <<end_year << '\n';
			continue;
		} 
		if(begin_year > current_year || begin_year < 1800)
		{
			cout << "Error: Invalid range " << begin_year << "-" <<end_year << '\n';
			continue;
		}
		if(end_year > current_year || end_year < 1800)
		{
			cout << "Error: Invalid range " << begin_year << "-" <<end_year << '\n';
			continue;
		}
		ofs << id << " " <<begin_year << " " << end_year << " " << operation <<" ";

		if(operation == "AVG")
		{
			double average_temperature = records.compute_average(id, begin_year, end_year);
			if (average_temperature == -99.99)
				ofs << "unknown" << endl;
			else
				ofs << average_temperature << endl;
		}

		if(operation == "MODE")
		{
			int mode = records.compute_mode(id, begin_year, end_year);
			if (mode == -99)
				ofs << "unknown" << endl;
			else
				ofs << mode << endl;
		}
	}


}
