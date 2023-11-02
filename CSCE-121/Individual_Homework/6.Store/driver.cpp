#include <iostream>
#include <vector>
#include <sstream>
#include "Product.h"
#include "Customer.h"

using namespace std;

int main() 
{
	try {
		//Product p(17, "Jill");
	Product p(123, "Clueless");
	//Customer c(456, "");

// Check if everything is initialized
cout<< p.getID()<<endl;
cout<< p.getName() <<endl;
cout << p.getInventoryCount()<<endl;
cout << p.getTotalPaid()<<endl;
cout << p.getNumberSold();
cout << p.getDescription();

// check direct setters
p.setDescription("This does some fun stuff.");
cout << "after set description: " << p.getDescription() <<endl;

p.setName("Knowing");
cout << "After set name" << (p.getName()) <<endl;

// Check if setName throws runtime_error for empty string
//cout << p.setName("");

// Check if everything is OK after exception thrown
cout << "ID:" << p.getID() <<endl;
cout << "Name: "<< p.getName() <<endl;
cout<<p.getInventoryCount() <<endl;
cout<<p.getTotalPaid()<<endl;
cout<<p.getNumberSold()<<endl;
cout<<p.getDescription()<<endl;


// Check if constructor throws runtime_error for empty string
// cout << "Expect error:" <<Product(654,"");

// check addShipment
p.addShipment(155, 1317.5);
//p.getTotalPaid()<<endl;
cout<< p.getInventoryCount()<<endl;
cout<<p.getNumberSold()<<endl;
cout<<p.getPrice()<<endl;

// // check addShipment for exceptions
// ASSERT_THROW(p.addShipment(-25,255.75),std::runtime_error);
// ASSERT_THROW(p.addShipment(25,-255.75),std::runtime_error);

// // make sure nothing was changed when encountering the exception
// ASSERT_EQ(p.getTotalPaid(),1317.5);
// ASSERT_EQ(p.getInventoryCount(),155);
// ASSERT_EQ(p.getNumberSold(), 0);
// ASSERT_EQ(p.getPrice(),10.625);

// // add another shipment to make sure adding or subtracting
// //  rather than assigning with new values
// p.addShipment(200, 500);
// ASSERT_NEAR(p.getTotalPaid(),1817.5,.1);
// ASSERT_EQ(p.getInventoryCount(),355);
// ASSERT_EQ(p.getNumberSold(), 0);
// ASSERT_NEAR(p.getPrice(),6.39965,0.00001);

// // test reduceInventory
// p.reduceInventory(175);
// ASSERT_NEAR(p.getTotalPaid(),1817.5,.1);
// ASSERT_EQ(p.getInventoryCount(),180);
// ASSERT_EQ(p.getNumberSold(), 175);
// ASSERT_NEAR(p.getPrice(),6.39965,0.00001);

// // invalid inputs to reduceInventory
// ASSERT_THROW(p.reduceInventory(-1),std::runtime_error);
// ASSERT_THROW(p.reduceInventory(181),std::runtime_error);

// // make sure nothing was changed when encountering the exception
// ASSERT_NEAR(p.getTotalPaid(),1817.5,.1);
// ASSERT_EQ(p.getInventoryCount(),180);
// ASSERT_EQ(p.getNumberSold(), 175);
// ASSERT_NEAR(p.getPrice(),6.39965,0.00001);

// // check price if values do not allow it to be calculated
// Product p2(283,"Something");
// ASSERT_THROW(p2.getPrice(),std::runtime_error);

// // One more shipment for good measure
// p.addShipment(1000, 100);
// ASSERT_NEAR(p.getTotalPaid(),1917.5,.1);
// ASSERT_EQ(p.getInventoryCount(),1180);
// ASSERT_EQ(p.getNumberSold(), 175);
// ASSERT_NEAR(p.getPrice(),1.76891,0.00001);

// // One more reduceInventory for good measure
// p.reduceInventory(500);
// ASSERT_NEAR(p.getTotalPaid(),1917.5,.1);
// ASSERT_EQ(p.getInventoryCount(),680);
// ASSERT_EQ(p.getNumberSold(), 675);
// ASSERT_NEAR(p.getPrice(),1.76891,0.00001);

// // double check that all getters return what is expected
// ASSERT_EQ(p.getID(),123);
// ASSERT_EQ(p.getName(),"Knowing");
// ASSERT_EQ(p.getDescription(),"This does some fun stuff.");
// ASSERT_EQ(p.getInventoryCount(),680);
// ASSERT_NEAR(p.getTotalPaid(),1917.5,.1);
// ASSERT_EQ(p.getNumberSold(), 675);
// ASSERT_NEAR(p.getPrice(),1.76891,0.00001);
		// cout << "p (id): " << p.getID() << endl;
		// cout << "p (name): " << p.getName() << endl;
		
		// Product q(183, "Tom");
		// cout << "q (id): " << q.getID() << endl;
		// cout << "q (name): " << q.getName() << endl;
		
		// Product badP(222, "");
		// cout << "badP (id): " << badP.getID() << endl;
		// cout << "badP (name): " << badP.getName() << endl;
		
		// p.setName("Jill Extreme");
		// cout << "p (name): " << p.getName() << endl;
		
		// q.setName("");
		// cout << "q (name): " << q.getName() << endl;	
		
		// cout << "Before 1st shipment" << endl;
		// cout << "inventory: " << p.getInventoryCount() << endl;
		// cout << "totalPaid: " << p.getTotalPaid() << endl;

		// p.addShipment(88, 230.44);

		// cout << "After 1st shipment" << endl;
		// cout << "inventory: " << p.getInventoryCount() << endl;
		// cout << "totalPaid: " << p.getTotalPaid() << endl;
		
		// p.addShipment(133, 142.11);
		// cout << p << endl;
		// cout << "After 2nd shipment" << endl;
		// cout << "inventory: " << p.getInventoryCount() << endl;
		// cout << "totalPaid: " << p.getTotalPaid() << endl;
		
		// cout << "Testing negative quantity" << endl;
		
		// p.addShipment(-5, 22.55);
		
		// cout << "Testing negative shipment cost" << endl; 
		cout << p << endl;
		
		// p.addShipment(5, -22.55);
	}
	catch (runtime_error& exc) {
		cout << "Exception caught: "<< exc.what() << endl;
	}
	
}