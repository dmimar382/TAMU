#include "Collection.h"
#include "Stress_ball.h"
#include "Jeans.h"



#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using CollectionSB = Collection <Stress_ball, Stress_ball_colors,Stress_ball_sizes>;
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

std::istream& operator>>(std::istream& is, CollectionSB& c)
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

using CollectionJN = Collection<Jeans, Jeans_colors, Jeans_sizes>;
void assign_jn_enum(std::string color, std::string size, int& jn_color_enum, int& jn_size_enum)
{
	if (color == "red")
		jn_color_enum = 0;
	else if (color == "blue")
		jn_color_enum = 1; 
	else if (color == "yellow")
		jn_color_enum = 2;
	else if (color == "green")
		jn_color_enum = 3;
	else if (color == "white")
		jn_color_enum = 4;
	else 
		jn_color_enum = 5;

	if (size == "small")
		jn_size_enum = 0;
	else if (size == "medium")
		jn_size_enum = 1;
	else if (size == "large")
		jn_size_enum = 2;
	else 
		jn_size_enum = 3;
}

std::istream& operator>>(std::istream& is, CollectionJN& c)
{
	std::string color;
	std::string size;
	int jn_color_enum;
	int jn_size_enum;

	while(is >> color >> size)
	{
		assign_jn_enum(color, size, jn_color_enum, jn_size_enum);
		Jeans jn1(static_cast<Jeans_colors>(jn_color_enum), static_cast<Jeans_sizes>(jn_size_enum));
		c.insert_item(jn1);
	}
	return is;
}

void test_stress_balls()
{
	srand(time(NULL));
  
  	cout <<endl;
	cout << "Default constructor test:" << endl;
	CollectionSB c1;
	c1.print_items();

	cout <<endl;
	cout << "Parameterized constructor test:" << endl;
	CollectionSB c2(4);
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
	CollectionSB c4;
	c4 = c1;
	cout <<"after assignment" << endl;
	Stress_ball sb8;
	c4.insert_item(sb8);
	c1.print_items();
	cout <<endl;
	c4.print_items();

	cout <<endl;
	cout << "Copy constructor test:" << endl;
	CollectionSB c5(c1);
	c5.insert_item(sb8);
	cout <<"after construction" << endl;
	c5.print_items();

	cout <<endl;
	cout << "Move constructor test:" << endl;
	CollectionSB c6 = std::move(c1);
	cout <<"after move construction" << endl;
	c6.print_items();

	cout <<endl;
	cout << "Move assignemnt test:" << endl;
	CollectionSB c7;
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
	CollectionSB c01;
	input_file1 >> c01; 
	//c01.print_items();

	//cout <<"File reading test 2 "<<endl;
	ifstream input_file2("stress_ball2.data");
	CollectionSB c02;
	input_file2 >> c02; 
	// c02.print_items();


	cout << endl;
	//cout <<"Output file test 1"<<endl;
	ofstream output_file1("sb_Output1.data");
	output_file1 << c01 <<endl;
	//cout << c01 <<endl;

	cout << endl;
	//cout <<"Output file test 2 "<<endl;
	ofstream output_file2("sb_Output2.data");
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
	CollectionSB c3 = make_union (c01,c02);
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


}

void test_jeans()
{
	srand(time(NULL));
  
  	cout <<endl;
	cout << "Default constructor test:" << endl;
	CollectionJN c1;
	c1.print_items();

	cout <<endl;
	cout << "Parameterized constructor test:" << endl;
	CollectionJN c2(4);
	c2.print_items();


	Jeans jn1;
	Jeans jn2;
	Jeans jn3;
	Jeans jn4;


	cout <<endl;
	cout << "Insertion test:" << endl;
	c1.insert_item(jn1);
	c1.insert_item(jn2);
	c1.insert_item(jn3);
	c1.insert_item(jn4);
	c1.print_items();

	cout <<endl;
	cout << "Copy assignment test:" << endl;
	CollectionJN c4;
	c4 = c1;
	cout <<"after assignment" << endl;
	Jeans jn8;
	c4.insert_item(jn8);
	c1.print_items();
	cout <<endl;
	c4.print_items();

	cout <<endl;
	cout << "Copy constructor test:" << endl;
	CollectionJN c5(c1);
	c5.insert_item(jn8);
	cout <<"after construction" << endl;
	c5.print_items();

	cout <<endl;
	cout << "Move constructor test:" << endl;
	CollectionJN c6 = std::move(c1);
	cout <<"after move construction" << endl;
	c6.print_items();

	cout <<endl;
	cout << "Move assignemnt test:" << endl;
	CollectionJN c7;
	c7 = std::move(c6);
	cout <<"after move assignemnt" << endl;
	c7.print_items();


	cout <<endl;
	cout << "Contains test:" << endl;
	Jeans jn5(Jeans_colors::green, Jeans_sizes::medium);
	c7.contains(jn5);

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
	cout << "Total items: " << c7.total_items(Jeans_colors::green) <<endl;
	cout << "Total items: " << c7.total_items(Jeans_sizes::small) <<endl;


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
	ifstream input_file3("jeans1.data");
	CollectionJN c01;
	input_file3 >> c01; 
	//c01.print_items();

	//cout <<"File reading test 2 "<<endl;
	ifstream input_file4("jeans2.data");
	CollectionJN c02;
	input_file4 >> c02; 
	// c02.print_items();


	cout << endl;
	//cout <<"Output file test 1"<<endl;
	ofstream output_file3("jeans_Output1.data");
	output_file3 << c01 <<endl;
	//cout << c01 <<endl;

	cout << endl;
	//cout <<"Output file test 2 "<<endl;
	ofstream output_file4("jeans_Output2.data");
	output_file4 << c02 <<endl;
	//cout << c02 <<endl;

	// cout <<endl;
	// cout << "Bubble sort test Collection 1: " <<endl;
	// c01.print_items();
	// cout <<endl;
	// sort_by_size(c01,Sort_choice::bubble_sort);
	// cout <<endl <<"After sort"<<endl;
	// c01.print_items();
	// cout << "Total number of Stress balls in C1: " << c01.total_items() <<endl;
	// cout << "Total number of RED Stress balls in C1: " << c01.total_items(Jeans_colors::red) << endl;

	// cout <<endl;
	// cout << "Bubble sort test Collection 2: " <<endl;
	// c02.print_items();
	// cout <<endl;
	// sort_by_size(c02,Sort_choice::bubble_sort);
	// cout <<endl <<"After sort"<<endl;
	// c02.print_items();
	// cout << "Total number of Stress balls in C2: " << c02.total_items() <<endl;
	// cout << "Total number of RED Stress balls in C2: " << c02.total_items(Jeans_colors::red) << endl;


	cout <<endl;
	cout << "Insertion sort test Collection 1:" <<endl;
	c01.print_items();
	cout <<endl;
	sort_by_size(c01,Sort_choice::insertion_sort);
	cout <<endl <<"After sort:"<<endl;
	c01.print_items();
	cout << "Total number of Stress balls in C1: " << c01.total_items() <<endl;
	cout << "Total number of RED Stress balls in C1: " << c01.total_items(Jeans_colors::red) << endl;

	cout <<endl;
	cout << "Insertion sort test Collection 2: " <<endl;
	c02.print_items();
	cout <<endl;
	sort_by_size(c02,Sort_choice::insertion_sort);
	cout <<endl <<"After sort"<<endl;
	c02.print_items();
	cout << "Total number of Stress balls in C2: " << c02.total_items() <<endl;
	cout << "Total number of RED Stress balls in C2: " << c02.total_items(Jeans_colors::red) << endl;

	cout <<endl;
	cout << "Selection sort test:" <<endl;
	c01.print_items();
	cout <<endl;
	sort_by_size(c01, Sort_choice::selection_sort);
	cout <<endl <<"After sort:"<<endl;
	c01.print_items();
	cout << "Total number of Stress balls in C1: " << c01.total_items() <<endl;
	cout << "Total number of RED Stress balls in C1: " << c01.total_items(Jeans_colors::red) << endl;

	cout <<endl;
	cout << "Selection sort test Collection 2: " <<endl;
	c02.print_items();
	cout <<endl;
	sort_by_size(c02,Sort_choice::selection_sort);
	cout <<endl <<"After sort"<<endl;
	c02.print_items();
	cout << "Total number of Stress balls in C2: " << c02.total_items() <<endl;
	cout << "Total number of RED Stress balls in C2: " << c02.total_items(Jeans_colors::red) << endl;

	cout << endl;
	cout << "Make union test:" <<endl;
	CollectionJN c3 = make_union(c01,c02);
	c3.print_items();
	cout <<endl <<endl;
	cout << "Total items: " << c3.total_items() <<endl;
	cout << "Total red items: " << c3.total_items(Jeans_colors::red) << endl;
	cout << "Total SMALL items: " <<c3.total_items(Jeans_sizes::small) << endl;


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


}


int main()
{
	int answer;
	cout << "What version to test: stress_ball (=0) or jeans (=1): ";
	cin >> answer;
	if (answer == 0)
		test_stress_balls();
	else if (answer == 1)
		test_jeans();
	else
		cout << "Wrong value: " << answer << endl;
	return 0;

}