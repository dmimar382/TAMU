#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>

using namespace std;

int main () {
	// vector <int> v;
	// v.push_back(7);
	// v.push_back(11);
	// int i {};

	// for(decltype(v.size()) i = 0; i<v.size(); ++i) {
	// 	cout <<v.at(i) <<endl;
	// }


 //   vector <string> words {};
 //   for (string s; cin >> s && s != "quit"; )
 //       words.push_back(s);
 //   for (decltype(words.size()) i = 0; i < words.size(); ++i)
 //       cout << words.at(i) << endl;

    random_device r_dev{};
    default_random_engine d_engine{r_dev()};
	return 0;
}