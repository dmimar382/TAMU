#include <iostream>
#include "LinkedList.h"
using namespace std;

int main()
{
    /*
    LinkedList l1("LinkedList l1");
    l1.insert_back(10);
    l1.insert_back(11);

    LinkedList l2("LinkedList l2");
    cout << l1 << endl;
    cout << l2 << endl << endl;
    */

    
    LinkedList<int> l1("LinkedList<int> l1");
    l1.insert_back(10);
    l1.insert_back(11);

    LinkedList<int> l2("LinkedList<int> l2");
    cout << l1 << endl;
    cout << l2 << endl << endl;
    

    l2 = l1;
    l2.insert_back(7);
    cout << l1 << endl;
    cout << l2 << endl << endl;

    
    LinkedList<double> l3("LinkedList<double> l3");
    l3.insert_back(11.0);
    l3.insert_back(9.0);

    LinkedList<double> l4("LinkedList<double> l4");
    l4.insert_back(13.0);
    cout << l3 << endl;
    cout << l4 << endl << endl;

    l4 = l3;
    l4.insert_front(3.0);
    cout << l3 << endl;
    cout << l4 << endl << endl;
    

    return 0;
}