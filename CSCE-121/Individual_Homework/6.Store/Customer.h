#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include "Product.h"

// note cannot have a "using namespace std;" statement in header file

class Customer {
	int id;
	std::string name;
	bool credit;
	double balance;
	std::vector <Product> productsPurchased;

	
public:
	Customer(int, std::string, bool credit = false);
	int getID() const;
	std::string getName() const;
	void setName(std::string);
	bool getCredit() const;
	void setCredit( bool hasCredit);
	double getBalance() const;
	void processPayment(double);
	void processPurchase(double, Product);
	std::string getProductsPurchased() const;

};

std::ostream& operator<<(std::ostream &os, const Customer& c);
#endif