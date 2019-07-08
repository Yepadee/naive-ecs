#include "Vec2D.h"
#include <math.h>

Vec2D::Vec2D(double x, double y)
{
	this->x = x;
	this->y = y;
}

Vec2D::~Vec2D()
{

}


double Vec2D::getX()
{
	return x;
}

double Vec2D::getY()
{
	return y;
}


double Vec2D::getMagnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

double Vec2D::crossProduct(Vec2D v2)
{
	return (getX() * v2.getY()) - (v2.getX() * getY());
}

double Vec2D::dotProduct(Vec2D v2)
{
	return (getX() * v2.getX()) + (getY() * v2.getY());
}


Vec2D Vec2D::getUnitVector()
{
	double magnitude = getMagnitude();
	return Vec2D(x / magnitude, y / magnitude);
}

Vec2D Vec2D::getLeftNormal()
{
	return Vec2D(-y, x);
}

Vec2D Vec2D::getRightNormal()
{
	return Vec2D(y, -x);
}


bool Vec2D::operator == (Vec2D v2)
{
	return getX() == v2.getX() && getY() == v2.getY();
}

bool Vec2D::operator != (Vec2D v2)
{
	return getX() != v2.getX() || getY() != v2.getY();
}

Vec2D Vec2D::operator * (double k)
{
	return Vec2D(x * k, y * k);
}

Vec2D Vec2D::operator + (Vec2D v2)
{
	return Vec2D(getX() + v2.getX(), getY() + v2.getY());
}

Vec2D Vec2D::operator - (Vec2D v2)
{
	return Vec2D(getX() - v2.getX(), getY() - v2.getY());
}
