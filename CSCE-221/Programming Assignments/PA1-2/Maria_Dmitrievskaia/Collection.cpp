#include "Collection.h"
#include "Stress_ball.h"
#include <fstream>
#include <stdexcept>

using namespace std;

//tested
Collection::Collection(){size = 0, capacity = 0, array = nullptr;}

//tested
Collection::Collection(int input_capacity)
{
	capacity = input_capacity;
	array = new Stress_ball[capacity];
}

//copy constructor 
Collection::Collection(const Collection &c2)
{
	size = c2.size;
	capacity = c2.capacity;
	Stress_ball* Array = new Stress_ball[capacity];
	for (int i =0; i < size; i++)
	{
		Array[i] = c2.array[i];
	}
	array = Array;
}

//copy assignment
Collection& Collection::operator=(Collection &c2)
{
	size = c2.size;
	capacity = c2.capacity;
	Stress_ball* Array = new Stress_ball[capacity];
	
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

//destructor
Collection::~Collection()
{
	size = 0;
	capacity = 0;
	delete[] array;
	array = nullptr;		 
}

//move constructor
Collection::Collection(Collection&& moving)
{
	array = moving.array;
	capacity = moving.capacity;
	size = moving.size;
	moving.array = nullptr;
	moving.capacity = 0;
	moving.size = 0;
}

//move assignment
Collection& Collection::operator=(Collection&& assign)
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

//private helper function for insert item
void Collection::resize()
{
	if( capacity == 0)
		capacity = 1;
	
	capacity = 2 * capacity;
	Stress_ball * new_array = new Stress_ball[capacity];
	
	for ( int i = 0; i < size; i++)
	{
		new_array[i] = array[i];
	}

	if (array != nullptr)
		delete []array;

	array = new_array;
}

void Collection::insert_item(const Stress_ball& sb)
{
	//cout << "Inserting:"<<endl;
	if (size == capacity)
		resize();
	array[size] = sb;
	size += 1;
}

bool Collection::contains(const Stress_ball& sb) const
{
	//cout << "Contains"<<endl;
	for (int i =0; i < size; i++)
		{
			if (array[i] == sb){
				cout << "true" <<endl;
				return true;
			}
		} 
	cout << "false" <<endl;
	return false;	 
}

Stress_ball Collection::remove_any_item()
{
	Stress_ball sb = array[rand()%(size-1)]; //Stress_ball sb;
	cout <<"Stress ball to remove:"<<  sb << endl;
	remove_this_item(sb);
	return sb;
	
}

//test if we need to remove two of the same stress balls
void Collection::remove_this_item(const Stress_ball& sb)
{
	if (size == 0)
		throw underflow_error("Collection is already empty");

	for (int i=0; i < size; ++i)
		if (array[i] == sb)
			for(int j = i; j < size-1; ++j)
				array[j] = array[j+1];
	size -= 1;
}

void Collection::make_empty()
{
	size = 0;
	capacity = 0;
	delete array;
	array = nullptr;	
}

bool Collection::is_empty() const
{
	if(size == 0){
		cout << "True" << endl;
		return true;
	}
	cout << "False" << endl;
	return false; 
}

int Collection::total_items() const
{
	return size;
}

int Collection::total_items(Stress_ball_sizes s) const
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

int Collection::total_items(Stress_ball_colors t) const
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

void Collection::print_items() const
{
	if (size == 0)
		cout << "Empty" <<endl;
	else
	{
		for (int i = 0; i < size; ++i)
			cout << array[i] << endl;
	}
}

Stress_ball& Collection::operator[](int i)
{
	for (int j = 0; j <= size; ++j)
	{
		if (j == i)
			return array[i];
		else
			continue;
	}
}

const Stress_ball& Collection::operator[](int i) const
{
	if(i > size)
		throw out_of_range("Out of range");
	for (int j = 0; j < size; ++j)
	{
		if (j == i)
			return array[i];
		else
			continue;
	}
}

std::istream& operator>>(std::istream& is, Collection& c)
{
	std::string color;
	std::string size;
	int sb_color_enum;
	int sb_size_enum;

	while(is >> color >> size)
	{
		assign_sb_enum(color, size, sb_color_enum, sb_size_enum);
		Stress_ball sb1(static_cast<Stress_ball_colors>(sb_color_enum), static_cast<Stress_ball_sizes>(sb_size_enum));
		c.insert_item(sb1);
	}
	return is;
}

void assign_sb_enum(std::string color, std::string size, int& sb_color_enum, int& sb_size_enum)
{
	if (color == "red")
		sb_color_enum = 0;
	else if (color == "blue")
		sb_color_enum = 1;
	else if (color == "yellow")
		sb_color_enum = 2;
	else
		sb_color_enum = 3;

	if (size == "small")
		sb_size_enum = 0;
	else if (size == "medium")
		sb_size_enum = 1;
	else 
		sb_size_enum = 2;
}

std::ostream& operator<<(std::ostream& os, const Collection& c)
{
	for(int i = 0; i < c.total_items();i++)
	{
		switch(c[i].get_color())
		{
			case Stress_ball_colors::red : os<< "(red, "; break;
			case Stress_ball_colors::blue : os<< "(blue, "; break;
			case Stress_ball_colors::yellow : os<< "(yellow, "; break; 
			case Stress_ball_colors::green : os<< "(green, "; break;
		}

		switch(c[i].get_size())
		{
			case Stress_ball_sizes::small : os<< "small)" <<endl; break;
			case Stress_ball_sizes::medium : os<< "medium)"<<endl; break;
			case Stress_ball_sizes::large : os<< "large)"<<endl; break; 
		}
	}
	return os;
}

Collection make_union(const Collection& c1, const Collection& c2)
{
	Collection c3(c1);
	for(int i = 0; i < c2.total_items(); i++)
		c3.insert_item(c2[i]);

	// c3.print_items(); 
	return c3;
}

void swap(Collection& c1, Collection& c2)
{
	Collection temp(std::move(c1));
	c1 = std::move(c2);
	c2 = std::move(temp);
}

void bubble_sort(Collection& c)
{
	for(int i = 0; i < c.total_items()-1; i++)
	{
		for(int j = 0; j <c.total_items()-i-1; j++)
		{
			if(c[j+1].get_size() < c[j].get_size())
			{
				//cout << "Swapping c[j] : " << c[j] << "and c[j+1]" << c[j+1] <<endl;
				Stress_ball temp = c[j+1];
				c[j+1] = c[j];
				c[j] = temp;
			}
		}
	}
}

void insertion_sort(Collection& c)
{
	for (int i = 1; i < c.total_items(); i++)
	{
		Stress_ball tmp = c[i];
		int j = i;
		for( ; j > 0 && tmp.get_size() < c[j-1].get_size(); j--)
			c[j] = c[j-1];
		c[j] = tmp;
	}
}
void selection_sort(Collection& c)
{
	for (int i = 0; i < c.total_items()-1; i++)
	{
		int index = i;
		for (int j = i+1; j < c.total_items(); j++)
			if (c[j].get_size() < c[index].get_size()) 
				index = j;
		Stress_ball tmp = c[i]; 
		c[i] = c[index];
		c[index] = tmp;
	}
}

void sort_by_size(Collection& c, Sort_choice sort)
{
	switch(sort)
	{
		case Sort_choice::bubble_sort: bubble_sort(c);break;
		case Sort_choice::insertion_sort: insertion_sort(c);break;
		case Sort_choice::selection_sort: selection_sort(c);break;
	}
}