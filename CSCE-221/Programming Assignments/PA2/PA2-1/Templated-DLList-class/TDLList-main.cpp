// testing the templated class DLList

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

#include "TemplatedDLList.h"

using namespace std;

int main ()
{
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DLList<string> dll;
  cout << "list: " << dll << endl << endl;

  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10; i<=100; i+=10) {
    stringstream ss;
    ss << i;
    dll.insert_last(ss.str());
  }
  cout << "list: " << dll << endl << endl;

  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10; i<=100; i+=10) {
    stringstream ss;
    ss << i;
    dll.insert_first(ss.str());
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Copy to a new list" << endl;
  DLList<string> dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  cout << "Assign to another new list" << endl;
  DLList<string> dll3;
  dll3 = dll;
  cout << "list3: " << dll3 << endl << endl;
  
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0; i<10; i++) {
    dll.remove_last();
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0; i<10; i++) {
    dll.remove_first();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;


  //Insert after
  cout << "Insert 93 after the 1st node:" << endl;
  dll2.insert_after(*(dll2.first_node()), "93");
  cout << "list2: " << dll2 << endl;
  cout <<endl;

  //Remove After
  cout << "Removing after the 1st node:" << endl;
  cout<<dll2.remove_after(*(dll2.first_node()));
  cout << "list2: " << dll2 << endl;
  cout <<endl;

  //Insert Before
  cout << "Insert 93 before the 1st node:" << endl;
  dll2.insert_before(*(dll2.first_node()), "93");
  cout << "list2: " << dll2 << endl;
  cout <<endl;

  //Remove Before
  cout << "Removing before the 1st node:" << endl;
  cout<<dll2.remove_before(*(dll2.first_node())->next);
  cout << "list2: " << dll2 << endl;
  cout <<endl;


  //Move Constructor
  cout <<endl;
  cout << "Move constructor test:" << endl;
  DLList<string> dll4 = std::move(dll2);
  cout <<"List after move construction: " << dll4 << endl <<endl;

  //Move assignment
  cout <<endl;
  cout << "Move assignemnt test:" << endl;
  DLList<string> dll5;
  dll5 = std::move(dll3);
  cout <<"List after move assignemnt: "<< dll5 <<endl << endl;
  // more testing...
  // add tests for insert_after, insert_before
  // add tests for remove_after, remove_before
  
  return 0;
}
