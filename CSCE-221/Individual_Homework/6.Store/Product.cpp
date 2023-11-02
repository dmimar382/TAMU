#include <iostream>
#include <string>
#include <stdexcept>
#include "Product.h"
#include <sstream>


using namespace std;

Product::Product(int id, string name) : id(id), name(name),
	inventory(0), numSold(0), totalPaid(0.0), description("") 
{
	if (name.length()==0) 
	{
		throw runtime_error("Product name cannot be empty.");
	}
}
	// Note a string's default constructor already sets the string to
	//   "" so we don't have to do that explicitly here
	//   I showed what it would look like but commented it out.

int Product::getID() const { return id; }

string Product::getName() const { return name; }

void Product::setName(string name) 
{
	if (name.length()==0) 
	{
		throw runtime_error("Product name cannot be empty.");
	}
	this->name = name; // could use an else, but it will only get here
	//   if there was not an exception!
}

string Product::getDescription() const { return description; }

void Product::setDescription(string description)
{
	this->description = description;
}

int Product::getNumberSold() const { return numSold; }

double Product::getTotalPaid() const { return totalPaid; }

int Product::getInventoryCount() const { return inventory; }

double Product::getPrice() const 
{
	if (inventory + numSold == 0)
	{
		throw runtime_error("Can't calculate a price.");
	}
	else
	{
		return ((totalPaid) / (static_cast<double>(inventory + numSold))) * 1.25;
	}
	// have to return something in stub so it will compile
	// will change later
}

void Product::addShipment(int quantity, double shipmentCost)
{
	if (quantity < 0)
	{
		throw runtime_error("Shipment quantity must be positive.");
	}
	if (shipmentCost < 0)
	{
		throw runtime_error("Shipment cost must be positive.");
	}
	//cout << "quantity: " << quantity << endl;
	//cout << "inventory: " << inventory << endl;
	inventory += quantity;
	totalPaid += shipmentCost;
}

void Product::reduceInventory(int quantity)
{
	if (quantity > inventory)
	{
		throw runtime_error("Not enough inventory.");
	}
	else if (quantity < 0)
	{
		throw runtime_error("Quantity is negative.");
	}
	else
	{
		inventory -= quantity;
		numSold += quantity;
	}
}
std::ostream& operator<<(std::ostream &os, const Product& p)
{
    os << "Product Name: "<< p.getName()<<"\nProduct ID: "<< p.getID()<<"\nDescription: "<< p.getDescription()<< "\nInventory: "<< p.getInventoryCount()<<"\nNumber Sold: "<<p.getNumberSold()<<"\nTotal Paid: "<<p.getTotalPaid(); 
    try { 
    os << "\nPrice: "<< p.getPrice() << "\n";
	} catch (runtime_error& badnum) {
		os << "\nPrice: Unavailable" << "\n";
	}
    return os;

}
// bool Product::operator== (const Product& e) const
// {


// 	return true;

// }


