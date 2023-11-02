#ifndef STRESS_BALL
#define STRESS_BALL
// #include <string>
// #include <ostream>

#include <iostream>

enum class Stress_ball_colors{red, blue, yellow, green};
enum class Stress_ball_sizes{small, medium, large};

class Stress_ball{
public:

	Stress_ball();
	Stress_ball(Stress_ball_colors, Stress_ball_sizes);
	Stress_ball_colors get_color() const;
	Stress_ball_sizes get_size() const;

	bool operator== (const Stress_ball& sb); 

private:
	Stress_ball_colors c;
	Stress_ball_sizes s;
};

std::ostream& operator<<(std::ostream& o, const Stress_ball& sb);

#endif