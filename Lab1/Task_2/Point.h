#pragma once
struct Point
{
	double x;
	double y;

	Point() : x(0), y(0)
	{
	}
	Point operator+=(const Point right) {
		this->x += right.x;
		this->y += right.y;
		return *this;
	}

	Point operator+(const Point right) const{ 
		Point result = *this;
		result += right;
		return result;
	}

	Point operator-=(const Point right) {
		this->x -= right.x;
		this->y -= right.y;
		return *this;
	}

	Point operator-(const Point right) const {
		Point result = *this;
		result -= right;
		return result;
	}
};

typedef struct Point Point;

