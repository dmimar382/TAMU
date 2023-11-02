/*
 * TemperatureData.h
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */
#include <string>

#ifndef TEMPERATUREDATA
#define TEMPERATUREDATA

struct TemperatureData {
	// Put data members here
	std::string id;
	int year; 
	int month; 
	double temperature;
	TemperatureData();
	TemperatureData(std::string id, int year, int month, double temperature);
	virtual ~TemperatureData();
	bool operator<(const TemperatureData& b);
};

#endif /* TEMPERATUREDATA */
