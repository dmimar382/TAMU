#ifndef STORE_H
#define STORE_H

#include <string>
#include <vector>
#include <iostream>
#include "Customer.h"

// note cannot have a "using namespace std;" statement in header file

class Store{
	std::string name;
	std::vector <Product> products;
	std::vector <Customer> customers;

	
public:
	Store();
	Store(std::string name);
	std::string getName() const;
	void setName(std::string name);
	void addProduct(int productID, std::string productName);
	Product& getProduct(int productID) ;
	void addCustomer(int customerID, std::string customerName, bool credit=false);
	Customer& getCustomer(int customerID);
	void takeShipment(int productID, int quantity, double cost);
	void takePayment(int customerID, double amount);
	void sellProduct(int customerID, int productID, int quantity);
	std::string listProducts();
	std::string listCustomers();

};

//std::ostream& operator<<(std::ostream &os, const Customer& c);
#endif