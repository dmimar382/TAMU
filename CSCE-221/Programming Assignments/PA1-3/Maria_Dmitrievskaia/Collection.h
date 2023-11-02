#ifndef COLLECTION
#define COLLECTION

#include "Stress_ball.h"
#include "Jeans.h"
#include "iostream"
#include <fstream>
#include <string>
#include <stdexcept>

template <class Obj, class F1, class F2>

class Collection{
public:
	Collection()
	{
		size = 0;
		capacity = 0; 
		array = nullptr;
	}

	Collection(int input_capacity)
	{
		capacity = input_capacity;
		array = new Obj[capacity];
	}

	//copy constructor
	Collection (const Collection &c2)
	{
		size = c2.size;
		capacity = c2.capacity;
		Obj* Array = new Obj[capacity];
		for (int i =0; i < size; i++)
		{
			Array[i] = c2.array[i];
		}
		array = Array;
	}

	//copy assignment 
	Collection& operator=(Collection &c2)
	{
		size = c2.size;
		capacity = c2.capacity;
		Obj* Array = new Obj[capacity];
		
		if (array != nullptr)
			delete[] array;
		for (int i =0; i < size; i++)
		{
			Array[i] = c2.array[i];
		}
		delete [] array;
		array = Array;
		return *this;	
	}

	~Collection()
	{
		size = 0;
		capacity = 0;
		delete[] array;
		array = nullptr;
	}

	//move constructor
	Collection(Collection&& moving)
	{
		array = moving.array;
		capacity = moving.capacity;
		size = moving.size;
		moving.array = nullptr;
		moving.capacity = 0;
		moving.size = 0;
	}

	//move assignment
	Collection& operator=(Collection&& assign)
	{
		if(this != &assign)
		 	delete [] array;
		array = assign.array;
		capacity = assign.capacity;
		size = assign.size;
		assign.array = nullptr;
		assign.capacity = 0;
		assign.size = 0;
		return *this;
	}

	void insert_item(const Obj& sb)
	{
		//std::cout << "Inserting:"<<std::endl;
		if (size == capacity)
			resize();
		array[size] = sb;
		size += 1;
	}

	bool contains(const Obj& sb) const
	{
		//std::cout << "Contains"<<std::endl;
		for (int i =0; i < size; i++)
			{
				if (array[i] == sb){
					std::cout << "true" <<std::endl;
					return true;
				}
			} 
		std::cout << "false" <<std::endl;
		return false;
	}

	Obj remove_any_item()
	{
		Obj sb = array[rand()%(size-1)]; //Stress_ball sb;
		std::cout <<"Stress ball to remove:"<<  sb << std::endl;
		remove_this_item(sb);
		return sb;
	
	}
	void remove_this_item(const Obj& sb)
	{
		if (size == 0)
			throw std::underflow_error("Collection is already empty");

		for (int i=0; i < size; ++i)
			if (array[i] == sb)
				for(int j = i; j < size-1; ++j)
					array[j] = array[j+1];
		size -= 1;
	}

	void make_empty()
	{
		size = 0;
		capacity = 0;
		delete array;
		array = nullptr;
	}

	bool is_empty() const
	{
		if(size == 0){
			std::cout << "True" << std::endl;
			return true;
		}
		std::cout << "False" << std::endl;
		return false; 
	}

	int total_items() const
	{
		return size;
	}

	int total_items(F2 s) const
	{
		int same_size = 0;
		for( int i = 0; i < size; i++)
		{
			if(array[i].get_size() == s)
				same_size += 1;
			else
				continue;
		}
		return same_size;

	}

	int total_items(F1 t) const
	{
		int same_color = 0;
		for( int i = 0; i < size; i++)
		{
			if((array[i].get_color()) == t)
				same_color += 1;
			else
				continue;
		}
		return same_color;
	}

	void print_items() const
	{
		if (size == 0)
			std::cout << "Empty" <<std::endl;
		else
		{
			for (int i = 0; i < size; ++i)
				std::cout << array[i] << std::endl;
		}
	}

	Obj& operator[](int i)
	{
		for (int j = 0; j <= size; ++j)
		{
			if (j == i)
				return array[i];
			else
				continue;
		}
	}

	const Obj& operator[](int i) const
	{
		if(i > size)
			throw std::out_of_range("Out of range");
		for (int j = 0; j < size; ++j)
		{
			if (j == i)
				return array[i];
			else
				continue;
		}
	}

private:
	Obj *array; //pointer to dynamically allocated memory
	int size; //logical size of array - the number of elements in use
	int capacity; //physical size of array
	void resize()
	{
		if( capacity == 0)
			capacity = 1;
		
		capacity = 2 * capacity;
		Obj * new_array = new Obj[capacity];
		
		for ( int i = 0; i < size; i++)
		{
			new_array[i] = array[i];
		}

		if (array != nullptr)
			delete []array;

		array = new_array;
	}

};


//STILL NEED TO WRITE THIS
template <typename Obj, typename F1, typename F2>
std::ostream& operator<<(std::ostream& os, const Collection<Obj, F1, F2>& c)
{
	for(int i = 0; i < c.total_items();i++)
		os<<c[i];
	return os;
}

template <class Obj, class F1, class F2>
Collection<Obj, F1, F2> make_union(const Collection<Obj, F1, F2>& c1, const Collection<Obj, F1, F2>& c2)
{
	Collection<Obj, F1, F2> c3(c1);
	for(int i = 0; i < c2.total_items(); i++)
		c3.insert_item(c2[i]);

	// c3.print_items(); 
	return c3;
}

template <class Obj, class F1, class F2>
void swap(Collection<Obj, F1, F2>& c1, Collection<Obj, F1, F2>& c2)
{
	Collection<Obj, F1, F2> temp(std::move(c1));
	c1 = std::move(c2);
	c2 = std::move(temp);
}

enum class Sort_choice {bubble_sort, insertion_sort, selection_sort};
template <class Obj, class F1, class F2>
void sort_by_size(Collection<Obj, F1, F2>& c, Sort_choice sort)
{
	switch(sort)
	{
		case Sort_choice::bubble_sort: bubble_sort(c);break;
		case Sort_choice::insertion_sort: insertion_sort(c);break;
		case Sort_choice::selection_sort: selection_sort(c);break;
	}
}

template <class Obj, class F1, class F2>
void bubble_sort(Collection<Obj, F1, F2>& c)
{
	for(int i = 0; i < c.total_items()-1; i++)
	{
		for(int j = 0; j <c.total_items()-i-1; j++)
		{
			if(c[j+1].get_size() < c[j].get_size())
			{
				//std::cout << "Swapping c[j] : " << c[j] << "and c[j+1]" << c[j+1] <<std::endl;
				Obj temp = c[j+1];
				c[j+1] = c[j];
				c[j] = temp;
			}
		}
	}
}

template <class Obj, class F1, class F2>
void insertion_sort(Collection<Obj, F1, F2>& c)
{
	for (int i = 1; i < c.total_items(); i++)
	{
		Obj tmp = c[i];
		int j = i;
		for( ; j > 0 && tmp.get_size() < c[j-1].get_size(); j--)
			c[j] = c[j-1];
		c[j] = tmp;
	}
}

template <class Obj, class F1, class F2>
void selection_sort(Collection<Obj, F1, F2>& c)
{
	for (int i = 0; i < c.total_items()-1; i++)
	{
		int index = i;
		for (int j = i+1; j < c.total_items(); j++)
			if (c[j].get_size() < c[index].get_size()) 
				index = j;
		Obj tmp = c[i]; 
		c[i] = c[index];
		c[index] = tmp;
	}
}

void test_stress_balls();
void test_jeans();


#endif
