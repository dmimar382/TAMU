/*
 * Write a program that asks the user to enter the following:
 * An integer representing the number of cents
 * 
 * You may assume that the number of cents entered is greater than or equal to 0
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
  * Ask the user to enter an amount in dollar
  * Divide the entered amount by quarter_value (25) to get a whole number bcs of integer division 
  * store result in number_of quarters, subract number of quarters*quarter_value from original number
  * Do this with every coin amount. new_amount= pennies in the end
  * 
  */ 

#include <iostream>

using namespace std;

int main() 
{
    cout << "Enter dollar amount: " <<endl;
//asking for user input 
    double amount {};
    cin >> amount;

//declaring constants for values of each coin    
    const int dollar_value {100}, quarter_value {25}, dime_value {10}, nickel_value {5};

    int new_amount {}, num_cents {};
    num_cents = amount * dollar_value;
    
 //once we have the dollar amount, we subtract those cents from the original value
//new_amount = amount % dollar_value has the same effect as the subtraction!!!!
    
    int quarters {};
    quarters = num_cents / quarter_value;
    new_amount = num_cents - (quarters * quarter_value);
    
    int dimes {};
    dimes = new_amount / dime_value;
    new_amount = new_amount - (dimes* dime_value);
    
    int nickels {};
    nickels = new_amount / nickel_value;
    new_amount = new_amount - (nickels * nickel_value);
    
    // Because all that is left are pennies, we can just set that equal to new_amount
    int pennies {};
    pennies = new_amount;  
    
    // Displaying results 
    cout << "quarters: " << quarters << endl;
    cout << "dimes: " << dimes << endl;
    cout << "nickels: " << nickels << endl;
    cout << "pennies: " << pennies << endl;

    return 0;
}
