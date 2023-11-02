#include "graph.h"

#include <vector>
#include <string>
#include <list>
#include <queue>
#include <fstream>
#include <iostream>


using namespace std;

// build a graph
void Graph::buildGraph(ifstream &input)
 {

 	int fromfile;
 	bool newline = true;
 	int num_index = 0;

 	while(input >> fromfile)
 	{
 		//cout << "Inside while loop" <<endl;
 		if (fromfile == -1)
 		{
 			newline = true;
 			num_index++;
 		}

 		else if(newline == true)
 		{
 			Vertex vertex(fromfile);
	  	node_list.push_back(vertex);
	  	newline = false;
      adj_list.push_back(new list<int>());
        // push back a new list 
 		}
 		else
 		{
 			adj_list.at(num_index)->push_back(fromfile);
 		}
 	}
 }

  // display the graph
void Graph::displayGraph()
{
 	for (int i = 0; i < node_list.size(); ++i)
 	{
 		Vertex v = node_list.at(i);
 		cout << v.label << ":";
 		list<int>* c = adj_list.at(i);

 		for(auto item: *c)
 		{
 			cout << item << " ";
 		}
 		cout << endl;
 	}
}

