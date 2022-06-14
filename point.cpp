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

bool point::inTab(int M) {
	return (x >= 0 && x < M && y >= 0 && y < M);

}

bool point::operator==(const point& point2)
{
	return (x==point2.x && y==point2.y);
}
