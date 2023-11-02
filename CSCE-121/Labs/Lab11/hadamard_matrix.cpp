//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                           LW: Hadamard matrix                            //
//                           hadamard_matrix.cpp                            //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                                #includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <vector>
#include "hadamard_matrix.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//                           function definitions                           //
//////////////////////////////////////////////////////////////////////////////
/*****************************************************************************
*                    vector<vector<bool>> hadamard(int n)                    *
*                                                                            *
*       Description ....:                                                    *
*                                                                            *
*                                                                            *
* Written By :                          Environment :                        *
* Date ......:                          Compiler ...:                        *
*****************************************************************************/
vector<vector<bool>> hadamard(int n)
{
    vector<vector<bool>> v (1, vector<bool>(1));
    v.at(0).at(0) = 1;

    for (int i = 0; i < (n-1); ++i){
    	int size = v.size();
    	//Creating the third quadrant
    	for (int j = 0; j < size; j++){
    		v.push_back(v.at(j));
    	} 
    	//Creating the second quadrant
    	for (int j = 0; j < size; j++) { 
    		for(int k = 0; k < size; k++) { 
    			v.at(j).push_back(v.at(j).at(k));
    		}
    	} 
    	for (int j = size; j < 2*size; j++) { 
    		for(int k = 0; k < size; k++) { 
    			v.at(j).push_back(!v.at(j).at(k)); 
    		} 
    	}


    }





    // continue implementation.

    return v;
}
/*****************************************************************************
*                 void print (vector <vector<bool>> const&v)                 *
*                                                                            *
*       Description ....:                                                    *
*                                                                            *
*                                                                            *
* Written By :                          Environment :                        *
* Date ......:                          Compiler ...:                        *
*****************************************************************************/
void print (vector <vector<bool>> const&v)
{
	for (auto i: v) {
		for(auto j: i) { 
			cout << j; 
		}
		cout << endl;
	}
}

/*****************************************************************************
*                          int str_to_int(std::string)                       *
*                                                                            *
*       Description ....:                                                    *
*                                                                            *
*                                                                            *
* Written By :                          Environment :                        *
* Date ......:                          Compiler ...:                        *
*****************************************************************************/

int str_to_int(std::string s)
{
    stringstream ss {s}; int val;
    ss >> val;
    if (ss.fail()) {
        ss.ignore(numeric_limits<streamsize>::max(), '\n');
        ss.clear();
        throw runtime_error("Value provided not an integer");
    }

    return val;
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////