#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Node.h"
#include <sstream>
#include <cmath>
#include <vector>
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
double LinkedList::compute_average(string id, int begin_year, int end_year)
{
	//triverse through all the nodes, find the ones I need withing the range of years and in the needed location 
	//put the temperatures in a vector, or just start adding up all the values right away 
	// compute average 
	double sum = 0.0;
	int count = 0;
	double average_temperature = 0.0;

	Node* curr = head;
	while(curr)
	{
		if(id == curr->data.id && curr->data.year >= begin_year && curr->data.year <= end_year)
		{
			sum +=curr->data.temperature;
			++count;
		}
		curr = curr->next;
		
	}
	if(count == 0)
		 return -99.99;

	average_temperature = sum/count;
	//cout << "average_temperature " << average_temperature <<endl;
	return average_temperature;
}
int LinkedList::compute_mode(std::string id, int begin_year, int end_year)
{
	Node* curr = head;
	vector <int> count_temp(101,0);
	bool known = false;
	while(curr)
	{
		if(id == curr->data.id && curr->data.year >= begin_year && curr->data.year <= end_year)
		{
			count_temp.at((round(curr->data.temperature)+ 50))++;
			known = true;
		}
		curr = curr->next;
	}

	int max = -99;
	int location_max = 0;
	for (int i = 0; i < count_temp.size(); ++i)
	{
		if(max <= count_temp.at(i))
		{
			max = count_temp.at(i);
			location_max = i;
		}
	}
	if (known)
	{
		return location_max -50;
	}
	return -99;

		// cout << "Temps size: " << temps.size() <<endl;

	// for (int i = 0; i < temps.size();++i)
	// {
	// 	for (int j = i; j < temps.size(); ++j)
	// 	{
	// 		if(temps.at(i) == temps.at(j))
	// 		{
	// 			cout << "Temps at i and j " << temps.at(i) << " " <<temps.at(j) <<endl;
	// 			++count;
	// 		}
	// 		cout << "Count being pushed in:" << count <<endl;
	// 		// count_temps.push_back(count);
	// 		// count = 0;
	// 	}
	// 	count_temps.push_back(count);
	// 	count = 0;
	// }
	// cout << "Count size: " << count_temps.size() <<endl;
	// int max = count_temps.at(0);
	// int location_max;
	// for (int i = 0; i < count_temps.size(); ++i)
	// {
	// 	if(max < count_temps.at(i))
	// 	{
	// 		max = count_temps.at(i);
	// 		location_max = i;
	// 	}

	// }
	// mode = temps.at(location_max);
	// cout << "Mode: " << mode << endl;

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
