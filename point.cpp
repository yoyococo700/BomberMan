#include "point.hpp"
#include <iostream>


point::point(int x, int y)
{
	point::x = x;
	point::y = y;
}

void point::printPoint() {
	std::cout << "x=";
	std::cout << x;
	std::cout << "y=";
	std::cout << y;
	std::cout << "\n";
}
