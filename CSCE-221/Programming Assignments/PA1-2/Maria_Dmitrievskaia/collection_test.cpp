#include "Collection.h"
#include "Jeans.h"
#include "Stress_ball.h"

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	srand(time(NULL));
  
  	cout <<endl;
	cout << "Default constructor test:" << endl;
	Collection c1;
	c1.print_items();

	cout <<endl;
	cout << "Parameterized constructor test:" << endl;
	Collection c2(4);
	c2.print_items();


	Stress_ball sb1;
	Stress_ball sb2;
	Stress_ball sb3;
	Stress_ball sb4;


	cout <<endl;
	cout << "Insertion test:" << endl;
	c1.insert_item(sb1);
	c1.insert_item(sb2);
	c1.insert_item(sb3);
	c1.insert_item(sb4);
	c1.print_items();

	cout <<endl;
	cout << "Copy assignment test:" << endl;
	Collection c4;
	c4 = c1;
	cout <<"after assignment" << endl;
	Stress_ball sb8;
	c4.insert_item(sb8);
	c1.print_items();
	cout <<endl;
	c4.print_items();

	cout <<endl;
	cout << "Copy constructor test:" << endl;
	Collection c5(c1);
	c5.insert_item(sb8);
	cout <<"after construction" << endl;
	c5.print_items();

	cout <<endl;
	cout << "Move constructor test:" << endl;
	Collection c6 = std::move(c1);
	cout <<"after move construction" << endl;
	c6.print_items();

	cout <<endl;
	cout << "Move assignemnt test:" << endl;
	Collection c7;
	c7 = std::move(c6);
	cout <<"after move assignemnt" << endl;
	c7.print_items();


	cout <<endl;
	cout << "Contains test:" << endl;
	Stress_ball sb5(Stress_ball_colors::green, Stress_ball_sizes::medium);
	c7.contains(sb5);

	cout <<endl;
	cout << "Remove any item:" <<endl;
	c7.remove_any_item();
	c7.print_items();

	cout << endl;
	cout << "Is empty:" <<endl;
	c7.is_empty();
	c7.print_items();

	cout << endl;

	cout << "Total items: " << c7.total_items() <<endl;
	cout << "Total items: " << c7.total_items(Stress_ball_colors::green) <<endl;
	cout << "Total items: " << c7.total_items(Stress_ball_sizes::small) <<endl;


	cout << endl;
	cout << "Make empty:" <<endl;
	c7.make_empty();
	c7.print_items();

	cout << endl;
	cout << "Is empty:" <<endl;
	c7.is_empty();
	c7.print_items();

///////////////////////////////////////////////////////////////////////////////
	//starting the input file part
	cout << endl;
	//cout <<"File reading test 1 "<<endl;
	ifstream input_file1("stress_ball1.data");
	Collection c01;
	input_file1 >> c01; 
	//c01.print_items();

	//cout <<"File reading test 2 "<<endl;
	ifstream input_file2("stress_ball2.data");
	Collection c02;
	input_file2 >> c02; 
	// c02.print_items();


	cout << endl;
	//cout <<"Output file test 1"<<endl;
	ofstream output_file1("Output1.data");
	output_file1 << c01 <<endl;
	//cout << c01 <<endl;

	cout << endl;
	//cout <<"Output file test 2 "<<endl;
	ofstream output_file2("Output2.data");
	output_file2 << c02 <<endl;
	//cout << c02 <<endl;

	// cout <<endl;
	// cout << "Bubble sort test Collection 1: " <<endl;
	// c01.print_items();
	// cout <<endl;
	// sort_by_size(c01,Sort_choice::bubble_sort);
	// cout <<endl <<"After sort"<<endl;
	// c01.print_items();
	// cout << "Total number of Stress balls in C1: " << c01.total_items() <<endl;
	// cout << "Total number of RED Stress balls in C1: " << c01.total_items(Stress_ball_colors::red) << endl;

	// cout <<endl;
	// cout << "Bubble sort test Collection 2: " <<endl;
	// c02.print_items();
	// cout <<endl;
	// sort_by_size(c02,Sort_choice::bubble_sort);
	// cout <<endl <<"After sort"<<endl;
	// c02.print_items();
	// cout << "Total number of Stress balls in C2: " << c02.total_items() <<endl;
	// cout << "Total number of RED Stress balls in C2: " << c02.total_items(Stress_ball_colors::red) << endl;


	cout <<endl;
	cout << "Insertion sort test Collection 1:" <<endl;
	c01.print_items();
	cout <<endl;
	sort_by_size(c01,Sort_choice::insertion_sort);
	cout <<endl <<"After sort:"<<endl;
	c01.print_items();
	cout << "Total number of Stress balls in C1: " << c01.total_items() <<endl;
	cout << "Total number of RED Stress balls in C1: " << c01.total_items(Stress_ball_colors::red) << endl;

	cout <<endl;
	cout << "Insertion sort test Collection 2: " <<endl;
	c02.print_items();
	cout <<endl;
	sort_by_size(c02,Sort_choice::insertion_sort);
	cout <<endl <<"After sort"<<endl;
	c02.print_items();
	cout << "Total number of Stress balls in C2: " << c02.total_items() <<endl;
	cout << "Total number of RED Stress balls in C2: " << c02.total_items(Stress_ball_colors::red) << endl;

	cout <<endl;
	cout << "Selection sort test:" <<endl;
	c01.print_items();
	cout <<endl;
	sort_by_size(c01, Sort_choice::selection_sort);
	cout <<endl <<"After sort:"<<endl;
	c01.print_items();
	cout << "Total number of Stress balls in C1: " << c01.total_items() <<endl;
	cout << "Total number of RED Stress balls in C1: " << c01.total_items(Stress_ball_colors::red) << endl;

	cout <<endl;
	cout << "Selection sort test Collection 2: " <<endl;
	c02.print_items();
	cout <<endl;
	sort_by_size(c02,Sort_choice::selection_sort);
	cout <<endl <<"After sort"<<endl;
	c02.print_items();
	cout << "Total number of Stress balls in C2: " << c02.total_items() <<endl;
	cout << "Total number of RED Stress balls in C2: " << c02.total_items(Stress_ball_colors::red) << endl;

	cout << endl;
	cout << "Make union test:" <<endl;
	Collection c3 = make_union(c01,c02);
	c3.print_items();
	cout <<endl <<endl;
	cout << "Total items: " << c3.total_items() <<endl;
	cout << "Total RED items: " << c3.total_items(Stress_ball_colors::red) << endl;
	cout << "Total SMALL items: " <<c3.total_items(Stress_ball_sizes::small) << endl;


	cout << endl;
	cout << "Swap test" <<endl;
	cout << "Before swap:" <<endl;
	c01.print_items(); 
	cout <<endl;
	c02.print_items(); 
	cout <<endl;

	swap(c01, c02);

	cout << "After swap:" <<endl;
	c01.print_items(); 
	cout <<endl;
	c02.print_items();
	cout <<endl;

	return 0; //

}