#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <regex>
#include <utility>
#include "HashTable.hpp"

using namespace std;

// DO NOT MODIFY BELOW THIS LINE
class CSVEditor {
private:
    ifstream input;
    ifstream roster;
    ofstream output;
    regex regexPattern;
    HashTable<string>* hashTable;
public:
    CSVEditor(string& inputPath, string& rosterPath, string& outputPath, regex expr, int m); //h(x) = x mod m;
	~CSVEditor();
    void readCSVToTable();
    void writeCSVToFile();
	std::tuple<int, int, double> getStats(); //returns the HashTable stats in a tuple <minChainLen, maxChainLen, averageChainLen>
};

