#include <iostream>
#include <cstdlib>
#include "Jeans.h"
#include "Collection.h"
using namespace std;

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

int main(){
  srand(time(NULL));
  
  cout << "Default constructor test:\n";
  Jeans arr_test[5];
  for(int i = 0; i < 5; i++){
    arr_test[i] = Jeans();
    cout << i << ": " << arr_test[i] << endl;
  }

  cout << "\nTwo arg constructor test:\n";
  Jeans test2(Jeans_colors::Red, Jeans_sizes::Small);
  cout << test2 << endl;

  Jeans test3(Jeans_colors::Green, Jeans_sizes::Large);
  cout << test3 << endl;

  cout << "\nCompare stress balls:\n";
  for (int i = 0; i < 5; i++) {
    if (arr_test[i] == test2) {
      cout << "arr_test[" << i << "] equal test2\n";
    } else if (arr_test[i] == test3) {
      cout << "arr_test[" << i << "] equal test3\n";
    } else {
      cout << "arr_test["<< i << "] not equal test2 nor test3\n";
    }
  }
  
}