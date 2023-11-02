// topological sort

#include <iostream>
#include "graph.h"
using namespace std;

void Graph::compute_indegree()
{	
	vector<int> h(node_list.size());
	for (int i = 0; i < node_list.size(); ++i)
  {
 		list<int>* c = adj_list.at(i);
 		for(int item : *c)
 		{
 			h.at(item-1) +=1;
 		}
 	}

 	for (int i = 0; i < h.size(); i++)
 	{	
 		Vertex& v = node_list.at(i);	
 		v.indegree = h.at(i);
 		//cout << "Indegree: " << v.indegree << endl;
 	}
}

void Graph::topological_sort()
{
	queue<Vertex*> q;
	int counter = 0;

	//cout << "Size : " << q.size() <<endl;
	//q.makeEmpty();

	for (int i = 0; i < node_list.size(); ++i)
  { 
	 	if(node_list.at(i).indegree == 0)
	 	{
	 		q.push(&node_list.at(i));
	 	}
	}

	while(!q.empty())
	{
		Vertex* ver = q.front();
		q.pop();

		list<int>* c = adj_list.at(ver->label-1);
		ver->top_num = ++counter;

  	for(auto item : *c)
  	{
      Vertex& w = node_list.at(item-1) ; 

 			if(--w.indegree == 0)
 				  q.push(&w);
		}

	}

  if (counter != node_list.size())
    throw CycleFoundException("Cycle found: illegal input");

} 
void Graph::print_top_sort()
{
  cout << "Topological sort: " ;
  for (int i = 0; i < node_list.size(); ++i)
  {
    cout << node_list.at(i).top_num << " "; 
  }
}

