#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include "Customer.h"
#include "Product.h"


using namespace std;

Customer::Customer(int customerID, string name, bool credit): id(customerID), name(name), credit(credit),balance(0.0)
{
	if (name.length()==0)
	{
		throw runtime_error("Product name cannot be empty.");
	} 
	
}

int Customer::getID() const{return id;}


string Customer::getName() const {return name;}


void Customer::setName(std::string name)
{
	if (name.length()==0)
	{
		throw runtime_error("Name cannot be an empty string.");
	} 

	this -> name = name;
}

bool Customer::getCredit() const {return credit;}


void Customer::setCredit(bool hasCredit)
{
	this -> credit = hasCredit;
}

double Customer::getBalance() const {return balance;}


void Customer::processPayment(double amount)
{
	if (amount < 0)
	{
		throw runtime_error("Amount is negative.");
	}

	else
	{
		balance+=amount;
	}
}


void Customer::processPurchase(double amount, Product product)
{
	if(credit)
	{
		balance -= amount;
	}
	else//credit ='[[[[[[[' false 
	{
		if(balance >= amount)
		{
			balance -= amount;
		}
		else
		{
			throw runtime_error("Not enough money in balance.");
		}
	}
	if (amount < 0)
	{
		throw runtime_error("Amount is less than 0. ");
	}


	productsPurchased.push_back(product); 
}

string Customer::getProductsPurchased() const
{
	stringstream output;
	output << "";
	
	for (int i = 0; i < productsPurchased.size();++i)
	{
		Product p = productsPurchased.at(i);
		output <<  "Product Name: " << p.getName() << "\nProduct ID: " << p.getID() << "\n\n";
	}
	return output.str();
}

std::ostream& operator<<(std::ostream &os, const Customer& c)
{
	string stringCredit = "false";
	if (c.getCredit())
		stringCredit = "true";

	os << "Customer Name: " << c.getName() <<"\nCustomer ID: " << c.getID() << "\nHas Credit: " << stringCredit << "\nBalance: " << c.getBalance() << "\nProducts Purchased --\n\n" << c.getProductsPurchased();
	return os;
}