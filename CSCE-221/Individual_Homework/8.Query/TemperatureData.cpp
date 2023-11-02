/*
 * TemperatureData.cpp
 *
 *  Created on: Jul 16, 2018
 *      Author: student
 */

#include "TemperatureData.h"
using namespace std;
#include <string>

TemperatureData::TemperatureData() : year(1800), month(0), temperature(0.0){} //initialize everything

TemperatureData::TemperatureData(std::string id, int year, int month, double temperature):id(id), year(year), month(month), temperature(temperature) {} //initialize everything


TemperatureData::~TemperatureData() {} // You should not need to implement this

bool TemperatureData::operator<(const TemperatureData& b) 
{
	if (id == b.id)
	{
		if (year == b.year)
		{
			if (month < b.month)
				return true;
			return false;
		}
		if(year < b.year)
			return true;
		return false;
	}
	if (id < b.id)
		return true;
	return false;
}

