#include "Jeans.h"

#include <iostream>
#include <cstdlib>



using namespace std;

Jeans::Jeans() 
{
	c = Jeans_colors(rand()%6);
	s = Jeans_sizes(rand()%4);
}

Jeans::Jeans(Jeans_colors usercolor, Jeans_sizes usersize)
{
	c = usercolor;
	s = usersize;
}

Jeans_colors Jeans::get_color() const
{
	return c;
}

Jeans_sizes Jeans::get_size() const
{
	return s;
}

bool Jeans::operator== (const Jeans& jn)
{
	if (c == jn.get_color() && s == jn.get_size())
		return true;
}

std::ostream& operator<<(std::ostream& o, const Jeans& jn)
{
	switch(jn.get_color())
	{
		case Jeans_colors::red : o<< "(red, "; break;
		case Jeans_colors::blue : o<< "(blue, "; break;
		case Jeans_colors::yellow : o<< "(yellow, "; break; 
		case Jeans_colors::green : o<< "(green, "; break;
		case Jeans_colors::white : o<< "(white, "; break;
		case Jeans_colors::brown : o<< "(brown, "; break;
	}

	switch(jn.get_size())
	{
		case Jeans_sizes::small : o<< "small)"; break;
		case Jeans_sizes::medium : o<< "medium)"; break;
		case Jeans_sizes::large : o<< "large)"; break;
		case Jeans_sizes::xlarge : o<< "xlarge)"; break; 	
	}

	return o;
}

