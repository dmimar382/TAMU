#include "Stress_ball.h"

#include <iostream>
#include <cstdlib>


using namespace std;

Stress_ball::Stress_ball() 
{
	c = Stress_ball_colors(rand()%4);
	s = Stress_ball_sizes(rand()%3);
}

Stress_ball::Stress_ball(Stress_ball_colors usercolor, Stress_ball_sizes usersize)
{
	c = usercolor;
	s = usersize;
}

Stress_ball_colors Stress_ball::get_color() const
{
	return c;
}

Stress_ball_sizes Stress_ball::get_size() const
{
	return s;
}


bool Stress_ball::operator== (const Stress_ball& sb)
{
	if (c == sb.get_color() && s == sb.get_size())
		return true;
}

std::ostream& operator<<(std::ostream& o, const Stress_ball& sb)
{
	switch(sb.get_color())
	{
		case Stress_ball_colors::red : o<< "(red, "; break;
		case Stress_ball_colors::blue : o<< "(blue, "; break;
		case Stress_ball_colors::yellow : o<< "(yellow, "; break; 
		case Stress_ball_colors::green : o<< "(green, "; break;
	}

	switch(sb.get_size())
	{
		case Stress_ball_sizes::small : o<< "small)"; break;
		case Stress_ball_sizes::medium : o<< "medium)"; break;
		case Stress_ball_sizes::large : o<< "large)"; break; 
	}

	return o;
}

