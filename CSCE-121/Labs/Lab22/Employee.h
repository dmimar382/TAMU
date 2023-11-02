#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <string>

class Employee {

	std::string name;
public:
	Employee();
	Employee(std::string);
	void set_name(std::string);
	std::string get_name() const;
	virtual std::string to_str() = 0;
	std::ostream& operator<<(std::ostream& os);
};

#endif