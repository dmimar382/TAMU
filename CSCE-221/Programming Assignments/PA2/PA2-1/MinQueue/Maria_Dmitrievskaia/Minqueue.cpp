#include "Minqueue.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main(){

	cout << "Create a new list" << endl;
  	Minqueue<int> q;
  	cout << "List: " << q << endl <<endl;

  	try 
  	{
  		cout << "Minimum empty: ";
  		q.min();
  	} 
  	catch ( exception &e)
  	{cerr << e.what() << endl <<endl;}

  	try
  	{
  		cout << "Dequeue empty:";
  		q.dequeue();
  	}
  	catch ( exception &e)
  	{cerr << e.what() << endl <<endl;}
 

  	cout << "Empty? " << endl;
 	cout << q.is_Empty() <<endl;

 	cout << "Size: " <<endl;
 	q.size();
 	cout << endl;

 	cout << "Enqueue: " <<endl;
 	for (int i=10; i<=100; i+=10) 
 		q.enqueue(i);
 	cout << q << endl;

 	cout << "Empty after enqueue? " << endl;
 	cout << q.is_Empty() <<endl;

 	cout << "Dequeue: " <<endl;
 	for (int i=0; i<50; i+=10) 
 		q.dequeue();
 	cout << q << endl;

 	cout <<"If there are multiple values that are the same, then q is: " << endl;
 	q.enqueue(60);
 	cout <<q <<endl;

 	cout << "Size: " <<endl;
 	q.size();
 	cout << endl;


 	cout << "MIN: " <<endl;
 	q.min();
 	cout << endl;

	return 0;
}