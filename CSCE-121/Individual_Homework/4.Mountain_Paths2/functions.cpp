#include<vector>
#include "functions.h"
#include <iostream>
#include <limits>

using namespace std;

int colorPath(const vector<vector<int>>& heightMap, vector<vector<int>>& r, vector<vector<int>>& g, vector<vector<int>>& b, int color_r, int color_g,
	int color_b, int start_row) 
{
	int dist = 0;
	//cout << "heightMap.size()-1 is " <<heightMap.size()-1 <<endl;
	//cout << "Start row is: " << start_row <<endl;

	int current_row = start_row;

	int up = numeric_limits<int>::max();
	int across = numeric_limits<int>::max();
	int down = numeric_limits<int>::max();


	for (int column = 0; column < heightMap.at(0).size(); column++)
	{
		r.at(current_row).at(column) = color_r;
		g.at(current_row).at(column) = color_g;
		b.at(current_row).at(column) = color_b;

		if (column ==heightMap.at(0).size()-1)
		{
			// r.at(current_row).at(column) = color_r;
			// g.at(current_row).at(column) = color_g;
			// b.at(current_row).at(column) = color_b;
			break;
		}

		// Testing to see which row we are on and what the up, across and down values are:
		if (current_row == 0)
		{
			up = numeric_limits<int>::max();
			down = abs(heightMap.at(current_row).at(column) - heightMap.at(current_row+1).at(column+1));
		}
		else if(current_row == heightMap.size()-1)
		{
			up = abs(heightMap.at(current_row).at(column) - heightMap.at(current_row-1).at(column+1));
			down = numeric_limits<int>::max();
			//cout << "Are we here?" << endl;
		}
		else
		{
			up = abs(heightMap.at(current_row).at(column) - heightMap.at(current_row-1).at(column+1));
			down = abs(heightMap.at(current_row).at(column) - heightMap.at(current_row+1).at(column+1));
		}

		across =abs(heightMap.at(current_row).at(column) - heightMap.at(current_row).at(column+1));
		
		//cout << up << " " << across << " " << down << " " <<endl;	



		if (up < across && up < down)
		{
			current_row -= 1;
			dist += up;
		}
		else if (down < up && down < across)
		{
			current_row += 1;
			dist += down;
		}
		else if (across == up || across == down)
		{
			current_row = current_row;
			dist += across;
		}
		else if (up == down && up<across)
		{ //current_row !=0
			current_row += 1;
			dist += down; 
		}
		else if (across < up && across < down)
		{
			current_row = current_row;
			dist += across;
		}

	}
		
	return dist;
}
