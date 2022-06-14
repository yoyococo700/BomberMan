#pragma once
class point
{
public:
	point(int x=0, int y=0);
	int x;
	int y;

	void printPoint();

	bool inTab(int );

	bool operator==(const point& point2);
};

