#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Node.h"
#include <sstream>
using namespace std;

LinkedList::LinkedList() {
	// Implement this function
	head = nullptr;
	tail = nullptr;
}

LinkedList::~LinkedList() {
	Node* next = nullptr;
	while (head) 
	{
		next = head->next;
		delete head;
		head = next;
	}
}

LinkedList::LinkedList(const LinkedList& source) 
{

	Node* curr = source.head;
	while (curr != nullptr) {
		insert(curr->data.id, curr->data.year, curr->data.month, curr->data.temperature);
		curr = curr->next;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& source)
{
	head = nullptr;
	tail = nullptr;
	Node* curr = source.head;
	while (curr != nullptr) {
		insert(curr->data.id, curr->data.year, curr->data.month, curr->data.temperature);
		curr = curr->next;
	}

}

void LinkedList::insert(string location, int year, int month, double temperature)
{ 
	Node* new_node = new Node(location, year, month, temperature);
	if( head == nullptr)
	{
		head = new_node;
		tail = new_node;
		return;
	}

	Node* curr = head;
	if(*new_node < *curr)
	{
		head = new_node;
		new_node->next = curr;
		return;
	}

	while(curr->next)
	{
		// if(curr->next == nullptr)
		// {
		// 	tail = new_node;
		// 	curr->next =tail;
			
		// }
		if(*new_node < *curr->next)
		{
			new_node->next = curr->next;
			curr->next = new_node;
			return;
				
		}
		curr = curr->next;
	}

	tail = new_node;
	curr->next = new_node;
	return;
}

void LinkedList::clear() {
	Node* next = nullptr;
	while (head) 
	{
		next = head->next;
		delete head;
		head = next;
	}
	// Implement this function
}

Node* LinkedList::getHead() const { 
	return head;
	// Implement this function it will be used to help grade other functions
}

string LinkedList::print() const {
	string outputString;
	stringstream ss;
	Node* curr = head;
	// Implement this function
	while (curr != nullptr) 
	{
		ss << curr->data.id << " " << curr->data.year << " " << curr->data.month << " " << curr->data.temperature << '\n';
		curr = curr->next;
	}
	outputString = ss.str();
	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
