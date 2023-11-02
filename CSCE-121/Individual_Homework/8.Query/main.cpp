#include "TemperatureDatabase.h"
#include "TemperatureData.h"
#include "LinkedList.h"
#include <cmath>

#include <iostream>
using namespace std;

int main(int argc, char** argv) {


	// TemperatureData T; 
	// TemperatureData L("Brenham", 1996, 10, 4.2); 
	// cout << T.year;
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " data_file query_file" << endl;
		return 1;
	} else {
		TemperatureDatabase database;
		database.loadData(argv[1]);
		database.performQuery(argv[2]); // Will be done in Part 2
	}
	//cout << round(5.5-0.01)<<endl;
	//cout << "Average for 3 = " << records.compute_average(id, begin_year, end_year);

	// ll.insert("mac", 2015, 7, 22.3);

	// cout << (ll.getHead(),nullptr);

	// Node* node = ll.getHead();
	// cout << node->data.id;//mac
	// cout << node->data.year; //2015
	// cout << node->data.month; //7
	// cout << node->data.temperature; //22.3
}
