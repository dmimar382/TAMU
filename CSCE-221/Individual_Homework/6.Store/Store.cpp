#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "Customer.h"
#include "Store.h"

using namespace std;

Store::Store(){}

Store::Store(string name):name(name)
{
	if (name.length()==0) 
	throw runtime_error("Product name cannot be empty.");
}
string Store::getName() const{return name;}

void Store::setName(string name)
{
	if (name.length()==0) 
		throw runtime_error("Name cannot be an empty string.");
	this -> name = name;
}

void Store::addProduct(int productID, string productName)
{
	for (int i =0; i < products.size();++i)
	{
		if (products.at(i).getID() == productID)
		{
			throw runtime_error("Products is already in there");
		}
	}
	Product p(productID, productName);
	products.push_back(p);
}

Product& Store::getProduct(int productID)
{
	
	for (int i =0; i< products.size(); ++i)
	{
		if (products.at(i).getID() == productID)
		{
			return products.at(i);
		}
	}
	
	throw runtime_error("Product is not in product list");

}
void Store::addCustomer(int customerID, string customerName, bool credit)
{
	for (int i =0; i < customers.size();++i)
	{
		if (customers.at(i).getID() == customerID)
		{
			throw runtime_error("Customer is already in there");
		}
	}
	Customer c(customerID, customerName, credit);
	customers.push_back(c);

}

Customer& Store::getCustomer(int customerID)
{
	
	for (int i =0; i< customers.size(); ++i)
	{
		if (customers.at(i).getID() == customerID)
		{
			return customers.at(i);
		}
	}

	throw runtime_error("Product is not in product list");

}

void Store::takeShipment(int productID, int quantity, double cost)
{//Find matching Product. If product is not in list of products throw an exception. Otherwise, update product with the shipment quantity and cost.
	Product& p = getProduct(productID); 
	p.addShipment(quantity, cost);


}

void Store::takePayment(int customerID, double amount)
{//Find matching customer and process the payment. If the customer does not exist, you should throw an exception or let an exception propagate that is thrown when you call another function to get the customer.
	Customer& c = getCustomer(customerID); 
	c.processPayment(amount);
}

void Store::sellProduct(int customerID, int productID, int quantity)
{
	Product& p = getProduct(productID); 
	Customer& c = getCustomer(customerID); 
	double p_price = quantity * p.getPrice(); 
	c.processPurchase(p_price, p); 
	p.reduceInventory(quantity);

}

string Store::listProducts()
{//Output information about each product. (Use overloaded output operator for Product.)
//Should not crash if price can’t be calculated. Output “Price: Unavailable” in that case.
	stringstream skrt;
	for(int i =0; i<products.size();++i)
	{
		skrt << products.at(i) << endl;
	}
	return skrt.str();

}

string Store::listCustomers()
{//Output information about each customer. (Use overloaded output operator for Customer.)
	stringstream iAmSoDone;
	for(int i =0; i<customers.size();++i)
	{
		iAmSoDone << customers.at(i) << endl;
	}
	return iAmSoDone.str();
	
}

