#ifndef MINQUEUE_H
#define MINQUEUE_H

#include <iostream>
#include "TemplatedDLList.h"
#include <stdexcept>


struct EmptyMinqueue : public std::runtime_error {
  explicit EmptyMinqueue(char const* msg=nullptr): runtime_error(msg) {}
};

template <typename T>
class Minqueue{
private:
	DLList<T> dll;
	int count;
public:
	bool is_Empty() const {return dll.is_empty();}
	void enqueue(int elem)
	{
		dll.insert_last(elem);
		count++;
	}

	int dequeue()
	{ 
		if (count == 0)
		{
			count = 0;
		}
		else
			count--;
		return dll.remove_first();
	}

	int size()
	{
  	 	cout << count;
  		return count;
	}

	T min()
	{

		if(is_Empty())
    		throw EmptyMinqueue("Empty");
		DLListNode<T> *node = dll.first_node();
		int min = node->obj;
  		while(node != dll.after_last_node())
  		{
  			if (node->obj <= min)
  				min = node->obj;
  			node = node->next;
  		}
  		cout << min;
  		return min;
	}

	DLList<T> get_dll() const
	{
		return dll;
	}

};

template <typename T>
ostream& operator<<(ostream& out, Minqueue<T> q)
{
	DLList<T> dll1 = q.get_dll();
	out << dll1;
	return out;
}
#endif