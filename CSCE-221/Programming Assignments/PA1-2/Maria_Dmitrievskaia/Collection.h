#ifndef COLLECTION
#define COLLECTION

#include "Stress_ball.h"
#include "iostream"
#include <fstream>
#include <string>

class Collection{
public:
	Collection();
	Collection(int input_capacity);
	Collection (const Collection &c2); //copy constructor
	Collection& operator=(Collection &c2); //copy assignment 
	~Collection();
	Collection(Collection&& move);//move constructor
	Collection& operator=(Collection&& assign);//move assignment
	void insert_item(const Stress_ball& sb);
	bool contains(const Stress_ball& sb) const;
	Stress_ball remove_any_item(); 
	void remove_this_item(const Stress_ball& sb);
	void make_empty();
	bool is_empty() const;
	int total_items() const;
	int total_items(Stress_ball_sizes s) const;
	int total_items(Stress_ball_colors t) const;
	void print_items() const;
	Stress_ball& operator[](int i);
	const Stress_ball& operator[](int i) const;

private:
	Stress_ball *array; //pointer to dynamically allocated memory
	int size; //logical size of array - the number of elements in use
	int capacity; //physical size of array
	void resize();

};

std::istream& operator>>(std::istream& is, Collection& c);
void assign_sb_enum(std::string, std::string, int&, int&);
std::ostream& operator<<(std::ostream& os, const Collection& c);
Collection make_union(const Collection& c1, const Collection& c2);
void swap(Collection& c1, Collection& c2);

enum class Sort_choice {bubble_sort, insertion_sort, selection_sort};
void sort_by_size(Collection& c, Sort_choice sort);
void bubble_sort(Collection& c);
void insertion_sort(Collection& c);
void selection_sort(Collection& c);

#endif
