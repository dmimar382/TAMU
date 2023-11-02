#include "CSVEditor.hpp"
#include <iostream>

CSVEditor::CSVEditor(string& inputPath, string& rosterPath, string& outputPath, regex expr, int m)
{
	input.open(inputPath);
	roster.open(rosterPath);
	output.open(outputPath);
	regexPattern = expr;
	hashTable = new HashTable<std::string>(m);
}

CSVEditor::~CSVEditor()
{
	delete hashTable;
}

void CSVEditor::readCSVToTable() 
{
	//std::cout <<"inside reading function" <<std::endl;

	string temp;
	int uin;
	string grade;

	while(getline(input, temp))
	{
		//cout << "Temp is:" <<temp <<endl;
		// regex expr(".*,.*,(.*),(.*)");
		smatch matched_result;
		regex_search(temp, matched_result, regexPattern);

		uin = std::stoi(matched_result[1]);
		grade =  matched_result[2];

		hashTable->insert(uin, grade);
	}

	// hashTable->search(800000046);
	// hashTable->search(800000151);
	// std::cout <<std::endl;
	
	// hashTable->minChainLen();
	// hashTable->maxChainLen();
}


void CSVEditor::writeCSVToFile()
{

	string Temp;
	int UIN;

	while(getline(roster, Temp))
	{
		//cout << "Temp is:" <<temp <<endl;
		// regex expr(".*,.*,(.*),(.*)");
		regex expression("(.*),(.*),(.*),.*");
		smatch matched_results;
		regex_search(Temp, matched_results, expression);

		UIN = std::stoi(matched_results[3]);

		if (hashTable->search(UIN) != NULL)
		{
			output << matched_results[1] << "," <<matched_results[2] <<"," << matched_results[3] <<"," << *hashTable->search(UIN) <<std::endl;
		}
		else 
		{
			output << matched_results[1] << "," <<matched_results[2] <<"," << matched_results[3] <<","<<endl;
		}
		
	}    
}

std::tuple<int, int, double> CSVEditor::getStats()
{

	int min = hashTable->minChainLen();
	int max = hashTable->maxChainLen();
	double average = hashTable->averageChainLen();

	return std::make_tuple(min, max, average);
}