// test of the DLList class

#include <iostream>
#include <cstdlib>
#include "DLList.h"

using namespace std;

int main ()
{
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  DLList dll;
  cout << "list: " << dll << endl << endl;

  cout <<endl;
  
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10; i <= 100; i+=10) {
    dll.insert_last(i);
  }
  cout << "list: " << dll << endl << endl;

  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10; i <= 100; i+=10) {
    dll.insert_first(i);
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Copy to a new list" << endl;
  DLList dll2(dll); 
  cout << "list2: " << dll2 << endl << endl; 
  
  cout << "Assign to another new list" << endl;
  DLList dll3;
  dll3 = dll;
  cout << "list3: " << dll3 << endl << endl;
  
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0; i < 10; i++) {
    dll.remove_last();
  }
  cout << "list: " << dll << endl << endl;
  
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0; i < 10; i++) {
    dll.remove_first();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;
  cout <<endl;

  // Insert After
  cout << "Insert 93 after the 1st node:" << endl;
  dll2.insert_after(*(dll2.first_node()), 93);
  cout << "list2: " << dll2 << endl;
  cout <<endl;

  //Remove After
  cout << "Removing after the 1st node:" << endl;
  dll2.remove_after(*(dll2.first_node()));
  cout << "list2: " << dll2 << endl;
  cout <<endl;

  //Insert Before
  cout << "Insert 93 before the 1st node:" << endl;
  dll2.insert_before(*(dll2.first_node()), 93);
  cout << "list2: " << dll2 << endl;
  cout <<endl;

  //Remove Before
  cout << "Removing before the 1st node:" << endl;
  dll2.remove_before(*(dll2.first_node())->next);
  cout << "list2: " << dll2 << endl;
  cout <<endl;

  //Move Constructor
  cout <<endl;
  cout << "Move constructor test:" << endl;
  DLList dll4 = std::move(dll2);
  cout <<"List after move construction: " << dll4 << endl <<endl;

  //Move assignment
  cout <<endl;
  cout << "Move assignemnt test:" << endl;
  DLList dll5;
  dll5 = std::move(dll4);
  cout <<"List after move assignemnt: "<< dll5 <<endl << endl;
  

  
  return 0;
}
