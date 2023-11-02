#include <iostream>
#include <string>


using namespace std;

int main(){

	string original string;
	getline(cin,original string);

	string user_input = original_string;
	string new_string;

//Step 1:
	for (int i = 0; i < user_input.length(); ++i){
		if ((user_input[i] >= 65 && user_input[i] <=90) ||(user_input[i] >=97 && user_input[i] <= 122) || (user_input[i] == 32))
		{
			new_string += user_input[i];
			//cout << new_string[i] << "1";
		}
	}

	string corrected_string2;
//Step 2:
	//Case 1:
	for (int i = 0; i < new_string.length(); ++i){
			if (new_string[i] >= 65 && new_string[i] <=90)
				new_string[i] = tolower(new_string[i]);
			if (new_string[i] == ' ')
				new_string[i] = 0;

			corrected_string2 += new_string[i];
	}

	cout << "Ignoring spaces and capital letters:" <<endl;
	for (int i = 0; i < user_input.length(); ++i){
		cout << corrected_string2[i];
		//cout << "2";
	}

	//Case 2:
	// for (int i = 0; i < new_string.length(); ++i){
	// 		if (new_string[i] == ' ')
	// 			new_string[i] = 0;

	// 		new_string2 += new_string[i];
	// }

	// cout << "Ignoring spaces and NOT capital letters:" <<endl;
	// for (int i = 0; i < user_input.length(); ++i){
	// 	cout << new_string2[i];
	// }


	//Case 3:
	// for (int i = 0; i < new_string.length(); ++i){
	// 	if (new_string[i] >= 65 && new_string[i] <=90)
	// 		new_string[i] = tolower(new_string[i]);

	// 	new_string2 += new_string[i];
	// }

	// cout << "Not Ignoring spaces and ignoring capital letters:" <<endl;
	// for (int i = 0; i < user_input.length(); ++i){
	// 	cout << new_string2[i];
	// }


	//Step 3:
	//flipping the existing string and storing it in a new string
	cout <<endl;
	string flipped;
	for (int i =0; i < corrected_string2.length(); ++i){
		flipped += corrected_string2[new_string.length()-1-i];
	}

	for (int i = 0; i < user_input.length(); ++i){
		cout << flipped[i];
	}

	return 0;
}