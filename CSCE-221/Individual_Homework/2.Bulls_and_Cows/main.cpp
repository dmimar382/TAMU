#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <cmath>

using namespace std;

int main() {
    srand(std::chrono::duration_cast<std::chrono::milliseconds>
     (std::chrono::system_clock::now().time_since_epoch()).count()%2000000000); 
    // needed to autograde some test cases in Mimir

//Initialization:
    int bulls {};
    int cows{};

//DONT FORGET TO PUT THE INPUT INTO A LOOP!!!!!!
    cout << "Enter number of digits in code (3, 4 or 5): ";
    int digits {};
    cin >> digits;
    
    if (digits == 0){
    	cout << "Enter code: ";
    	int code {};
    	cin >> code;

    	cout << "Enter number of digits in code: ";
    	cin >> digits;
        
        vector <int> vector_code (digits);
        int index {digits-1};
        int digit{};

        
        // Store the integer value into a vector   
        for( ;index >= 0; index--){
            digit = code % 10; 
            vector_code.at(index) = digit; 
            code /= 10; 
        }
        cout << "Number to guess: ";
        for ( int i {}; i < digits; ++i){
            if (i == digits - 1)
                cout << vector_code.at(i)<< endl;
            else
                cout << vector_code.at(i) << "-";
        }

        //Ask the user to continue guessing a number, until their guess is correct
        do{
           cout << "Enter guess: ";
           int guess {};
           cin >> guess;
           
           vector <int> vector_guess(digits);
           int index {digits-1};
           int digit{};
           
           // Store the guess value into a vector 
           for( ;index >= 0; index--){
               digit = guess % 10; 
               vector_guess.at(index) = digit; 
               guess /= 10; 
           }
           cout << "Vector you guessed: ";
           for ( int i {}; i < digits; ++i){
               if (i == digits - 1)
                   cout << vector_guess.at(i)<< endl;
               else
                   cout << vector_guess.at(i) << "-";
           }  

           bool is_different {false};
           //I need to loop through the guess vector and make sure every entered
           //value is different 

           //boolean && keep_working
           while (is_different != true){
            for( int j {0}; j < vector_guess.size(); ++j){
                for( int k {j+1}; k < vector_guess.size(); ++k){
                    cout << "The j index " << j << " and the k index " <<k <<" are being compared." <<endl;
                    if (vector_guess.at(j) == vector_guess.at(k)){
                        cout << "Each number must be different." <<endl;
                        return (is_different = false);
                    }
                    else{
                        is_different = true;
                    }
                    
                    cout << " The value of Different is: " << is_different << endl << endl;
                }
            }
            }   
        }
        while ( bulls != digits); 
    }

    return 0;
    }