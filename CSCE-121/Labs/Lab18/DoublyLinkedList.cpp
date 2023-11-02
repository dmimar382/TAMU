#include "DoublyLinkedList.h"
#include <iomanip>
#include <sstream>
using namespace std;

DoublyLinkedList::DoublyLinkedList()
{

}

DoublyLinkedList::DoublyLinkedList(int val)
{
	insert_front(val);
}

DoublyLinkedList::~DoublyLinkedList()
{
	Node* next = nullptr;
	while (head) 
	{
		next = head->next;
		delete head;
		head = next;
	}
}

void DoublyLinkedList::insert_back(int val)
{
	Node* n = new Node(val);
    if (head == nullptr)
        head = n;
    n->prev = tail; tail = n;
    if (n->prev != nullptr)
        n->prev->next = tail;

}

void DoublyLinkedList::insert_front(int val)
{
    Node* n = new Node(val);
    if (head == nullptr)
        tail = n;
    n->next = head; head = n;
    if (n->next != nullptr)
        n->next->prev = head;
}

void DoublyLinkedList::insert_at(int val, int idx)
{
	Node* n = new Node(val);
	if (head ==nullptr && idx>0)
	{
	throw runtime_error("error");
	}

	if (idx==0) 
	{
		insert_front(val);
		return;
	}

	Node* prior = head; 
	for (int i = 1; i < idx; ++i)
	{	
		if(!prior->next)
		{
			throw runtime_error("error");
		}

		prior = prior->next;		
	}

	if (!prior->next)
	{
		insert_back(val);
		return;
	}

	Node* later = prior->next; 

	n->prev = prior;
	n->next = later;
	prior->next = n;
	later->prev = n;


}

Node& DoublyLinkedList::find(int val)
{
	Node* curr = head;
	while (curr)
	{
		if (curr->data == val)
			return *curr;
		curr = curr->next;
	}
	throw runtime_error("error");
}

void DoublyLinkedList::delete_at(int idx)
{

	if (head == nullptr)
	{
		throw runtime_error("error");
	}
	//Node* n = new Node(val);
	Node* atIdx = head;
	//head = head -> next;

	if(idx == 0)
	{
		head = head -> next;
		atIdx->next->prev = nullptr;
		delete atIdx;
		return;
	}
	for (int i = 1; i <= idx; ++i)
	{	
		if(!atIdx->next)
		{
			throw runtime_error("error");
		}
		atIdx = atIdx->next;		
	}

	if(atIdx->next == 0)
	{
		tail= tail -> prev;
		atIdx->prev->next = nullptr;
		delete atIdx;
		return;
	}


	atIdx->next->prev = atIdx -> prev;
	atIdx->prev->next = atIdx ->next; 

	delete atIdx;

}

Node& DoublyLinkedList::get_head()
{
    return *head;
}

Node& DoublyLinkedList::get_tail()
{
    return *tail;
}

Node const& DoublyLinkedList::get_head() const
{
    return *head;
}

Node const& DoublyLinkedList::get_tail() const
{
    return *tail;
}

ostream& operator<<(ostream &os, DoublyLinkedList const& ll) {
    os << "Doubly Linked List" << endl;
    if (&(ll.get_head()) == nullptr)
        return (os << "Empty" << endl);
    os << "Head: " << &(ll.get_head()) << "\t Tail: " << &(ll.get_tail()) << endl;
    Node const* curr = &(ll.get_head());
    os << "Nodes (accessible from head to tail):" << endl << endl;
    os << setw(16) << setfill(' ') << ' ' << ' ' << center("prev", 15) << ' ' << center("data", 15) << ' ' << center("next", 15) << endl;
    while (curr != nullptr) {
        ostringstream oss; oss << (curr->prev); string prev = oss.str(); oss.str(""); oss << (curr->next); string next = oss.str(); oss.str(""); oss << (curr->data); string data = oss.str(); oss.str(""); oss << curr; string address = oss.str();
        os << setw(16) << setfill(' ') << ' ' << '.' << setw(16) << setfill('-') << '.' << setw(16) << '.' << setw(16) << '.' << endl;
        os << setw(16) << setfill(' ') << center(address,15) << '|' << setw(15) << setfill(' ') << center(prev, 15) << '|' << setw(15) << center(data, 15) << '|' << setw(15) << center(next, 15) << '|'<< endl;
        os << setw(16) << setfill(' ') << ' ' << '\'' << setw(16) << setfill('-') << '\'' << setw(16) << '\'' << setw(16) << '\'' << endl;
        os << endl;
        curr = curr->next;
    }
    return os;
}

string center (const string &str, const int col_width)
{
    // quick and easy (but error-prone) implementation
    int padl = (col_width - str.length()) / 2;
    int padr = (col_width - str.length()) - padl;
    string strf = string(padl, ' ') + str + string(padr, ' ');
    return strf;
}