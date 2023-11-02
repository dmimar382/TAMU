/*
 * Write a program that asks the user to enter the following:
 * An integer representing the number of cents
 * 
 * You may assume that the number of cents enterres is greater than or equal to 0
 * 
 * The program should then display how to provide that change to the user.
 * 
 * In the US:
 *  1 dollar is 100 cents
 *  1 quarter is 25 cents 
 *  1 dime is 10 cents 
 *  1 nickel is 5 cents 
 *  1 penny is 1 cent
 * 
 * Here is a sample run:
 * 
 * Enter the amount in cents: 92
 * 
 * dollars: 0
 * quarters: 3
 * dimes: 1
 * nickels : 1
 * pennies :2
 */
 
 
 /*Psuedocode
  * Ask the user to enter an amount in pennies
  * Divide the entered amount by quarter_value (25) to get a whole number bcs of integer division 
  * store result in number_of quarters, subract number of quarters*quarter_value from original number
  * Do this with every coin amount. new_amount= pennies in the end
  * 
  */ 

#include <iostream>

using namespace std;

int main() 
{
    cout << "Enter the amount in cents: " << endl;  //asking for user input 
    int amount {};
    cin >> amount;  //storing input in variable amount 
    
    const int dollar_value {100};   //declaring constants for values of each coin
    const int quarter_value {25};
    const int dime_value {10};
    const int nickel_value {5};

    int dollars {};     //initializing variable
    dollars = amount / dollar_value;    
    
    int new_amount{};
    new_amount = amount - (dollars * dollar_value); //once we have the dollar amount, we subtract those cents from the original value
                                                    //new_amount = amount % dollar_value has the same effect as the subtraction!!!!
    
    int quarters {};
    quarters = new_amount / quarter_value;
    new_amount = new_amount - (quarters * quarter_value);
    
    int dimes {};
    dimes = new_amount / dime_value;
    new_amount = new_amount - (dimes* dime_value);
    
    int nickels {};
    nickels = new_amount / nickel_value;
    new_amount = new_amount - (nickels * nickel_value);
    
    int pennies {};
    pennies = new_amount;   // because all that is left are pennies, we can just set that equal to new_amount
    
    cout << "dollars: " << dollars << endl;     //displaying results 
    cout << "quarters: " << quarters << endl;
    cout << "dimes: " << dimes << endl;
    cout << "nickels: " << nickels << endl;
    cout << "pennies: " << pennies << endl;

    return 0;
}
