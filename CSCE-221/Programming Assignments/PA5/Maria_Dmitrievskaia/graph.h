#ifndef GRAPH_H
#define GRAPH_H

//Need to initialize vector to a size
//ask about why while loop is terminating 
#include <vector>
#include <list>
#include <queue>
#include <fstream>
#include <stdexcept>

using namespace std;

struct CycleFoundException : public std::runtime_error {
  explicit CycleFoundException(char const* msg=nullptr): runtime_error(msg) {}
};


struct Vertex {
  int label; // unique int for a vertex
  int indegree; // Part 2
  int top_num = 0; // Part 2: topological sorting number
  Vertex(int l) : label(l) {}
  Vertex(int l, int ind) : label(l), indegree(ind) {} //Part 2
};

class Graph {
private:
  vector<Vertex> node_list;
  vector<list<int>*> adj_list;
public:
  Graph(){

  };  // default constructor

  ~Graph()
  {
    for (int i = 0; i < node_list.size(); ++i)
    {
      delete adj_list.at(i);
    }
  } 

  // build a graph
  void buildGraph(ifstream &input);
  // display the graph
  void displayGraph();
  

  
  // topological sort
  void topological_sort(); // Part 2
  // find indegree
  void compute_indegree(); // Part 2
  // print topological sort
   void print_top_sort();  // Part 2
};

#endif
