#ifndef JEANS
#define JEANS
// #include <string>
// #include <ostream>

#include <iostream>

enum class Jeans_colors{red, blue, yellow, green, white, brown};
enum class Jeans_sizes{small, medium, large, xlarge};

class Jeans{
public:

	Jeans();
	Jeans(Jeans_colors, Jeans_sizes);
	Jeans_colors get_color() const;
	Jeans_sizes get_size() const;

	bool operator== (const Jeans& jn); 

private:
	Jeans_colors c;
	Jeans_sizes s;
};

std::ostream& operator<<(std::ostream& o, const Jeans& jn);

#endif