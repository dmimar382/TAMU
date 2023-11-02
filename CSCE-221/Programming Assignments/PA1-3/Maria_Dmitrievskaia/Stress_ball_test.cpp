#include <iostream>
#include <cstdlib>
#include "Stress_ball.h"
#include "Collection.h"

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


int main(){
  srand(time(NULL));
  
  cout << "Default constructor test:\n";
  Stress_ball arr_test[5];
  for(int i = 0; i < 5; i++){
    arr_test[i] = Stress_ball();
    cout << i << ": " << arr_test[i] << endl;
  }

  cout << "\nTwo arg constructor test:\n";
  Stress_ball test2(Stress_ball_colors::red, Stress_ball_sizes::small);
  cout << test2 << endl;

  Stress_ball test3(Stress_ball_colors::green, Stress_ball_sizes::large);
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