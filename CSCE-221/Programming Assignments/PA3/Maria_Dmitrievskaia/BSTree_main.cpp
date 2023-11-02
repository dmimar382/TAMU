
#include <iostream>
#include <fstream>
#include <sstream>
#include "BSTree.h"
#include <string>

using namespace std;

BSTree read_file(string file_name)
{
//   /*
//     open the file and use the input operator (operator>>)
//     to construct a new tree
//   */
  ifstream ifs{file_name};   
  BSTree new_tree;

  if(!ifs.is_open())
  {
    cout << "Unable to open file" << endl;
    exit(1);
  }

  // int x {};

  // while(!ifs.eof())
  // {
  //   ifs >> x;
  //   new_tree.insert(x);
  // }

  ifs >> new_tree;
  return new_tree;
}

ofstream& write_file(ofstream& out, BSTree& tree , string file_name)
{
  //cout << "output operator" <<endl;
  out.open(file_name);
  if(!out.is_open())
  {
    cout << "Unable to open file" << endl;
    exit(1);
  }

  tree.print_level_by_level(out);
  return out;
}

ofstream& write_file_in_order(ofstream& out, BSTree& tree , string file_name)
{
  //cout << "output operator" <<endl;
  out.open(file_name);
  if(!out.is_open())
  {
    cout << "Unable to open file" << endl;
    exit(1);
  }
  tree.inorder(out);
  return out;
}


int main(){
  
  //What was given to us: 
  for(int i = 1; i <= 12; i++) {
    string dir= "data-files/"+std::to_string(i);
    string dir2 = "data-files-output/";

    BSTree l = read_file(dir+"l");
    cout << "average search time linear " << i << " "
	 << l.get_average_search_time() << endl << "size of linear: " << l.get_size() <<endl;


    BSTree p = read_file(dir+"p");
    cout << "average search time perfect "<< i << " "
	 << p.get_average_search_time() << endl<< "size of perfect: " <<p.get_size() <<endl;


    BSTree r = read_file(dir+"r");
    cout << "average search time random "<< i << " "
	 << r.get_average_search_time() << endl << "size of random: " << r.get_size() <<endl;

    if(i <= 4) 
    {
      cout << "prefect tree " << i << endl << p;

    }

    ofstream ofs;
    write_file_in_order(ofs, l, dir2 + std::to_string(i)+ "l.txt");
    ofstream ofs1;
    write_file_in_order(ofs1, p, dir2 + std::to_string(i)+ "p.txt");
    ofstream ofs2;
    write_file_in_order(ofs2, r, dir2 + std::to_string(i)+ "r.txt");


    cout << endl;
  }
// }

/////////////////////////////////////////////////////////////////////////////////////////////

//Testing reading from a file:
  cout << "Testing reading from a file: " <<endl;
  BSTree BS0 = read_file("Testing.txt");
  cout << BS0 << endl;

////Testing default constructor:
  cout << "Testing default constructor: " <<endl;
  BSTree BS1;
  cout << BS1 << endl;
  
//Testing search function with empty tree
  cout << "Testing search function with empty tree: " <<endl;
  BS1.search(4);

//Testing insert function 
  cout << "Testing insert function: " <<endl <<endl;
  BS1.insert(5);
  BS1.insert(5);
  BS1.insert(4);
  BS1.insert(10);
  BS1.insert(20);
  BS1.insert(1);
  BS1.insert(0);
  BS1.insert(22);

  //Testing Copy Constructor
  cout << "Testing Copy Constructor: " <<endl;
  BSTree BS2(BS1);
  cout << "BS1:" <<endl << BS1;
  cout << endl;
  cout << "BS2:" <<endl << BS2;
  cout << "Size of copied tree:" <<  BS2.get_size() <<endl <<endl;

//Testing Copy Assignemnt
  cout << "Testing Copy Assignemnt: " <<endl;
  BSTree BS3;
  BS3 = BS1;
  cout << "BS1:" <<endl << BS1;
  cout << endl;
  cout <<"BS3:" <<endl << BS3;
  cout << "Size of copied tree:" << BS3.get_size() <<endl <<endl;


//Testing BSTree output and average search time
  cout <<  "Testing BSTree output, update search time and average search time: " <<endl;
  cout <<"BS1: " <<endl << BS1;
  cout << "Average search time: "<< BS1.get_average_search_time() <<endl <<endl;\

//Testing seach function
  cout << "Testing Search function: " <<endl;
  cout << "Searching for 4: ";
  BS1.search(4);
  //cout <<endl;
  cout << "Searching for 7: ";
  BS1.search(7);
  cout << endl<<endl;



//Testing Move constructor
  cout << "Testing move constructor: " <<endl;
  BSTree BS4(std::move(BS1));
  cout  << "BS4: " <<endl << BS4 <<endl;
  cout << "BS1: " << BS1 <<endl;
  cout << BS1.get_size() <<endl;

  cout << endl;

//Testing Move assignment
  cout << "Testing move assignemnt: " <<endl;
  BSTree BS5;
  cout << "BS5 before calling move:" << BS5 <<endl;
  cout << "BS2 before calling move:" <<endl <<BS2 <<endl;
  BS5= std::move(BS2);
  cout  << "BS5 after moving: " <<endl << BS5 <<endl;
  cout << "BS2 after moving: " <<endl << BS2 <<endl;


  //Testing In Order function
  cout << "Testing in order traversal: " <<endl;   
  BS5.inorder(cout) <<endl;
  cout <<endl;

  cout << "Checking move assignment with self assignment: " <<endl;
  BS5 = std::move(BS5);
  cout << endl;



//Testing Destructor
  cout << "BS3 before destructor" <<endl << BS3 <<endl;
  BS3.~BSTree();
  cout << "BS3 after destructor" <<endl << BS3 <<endl;


//Testing move constructor and assignment with empty tree
  BSTree BS7 = std::move(BS3);
  cout << BS7 <<endl;

  BSTree BS6;
  BS6 = std::move(BS3);   


  return 0;
    
}

