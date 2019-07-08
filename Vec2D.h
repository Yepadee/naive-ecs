#pragma once
class Vec2D
{
public:
	Vec2D(double x, double y);
	~Vec2D();

	double getX();
	double getY();

	double getMagnitude();
	double dotProduct(Vec2D v2);
	double crossProduct(Vec2D v2);

	Vec2D getUnitVector();
	Vec2D getLeftNormal();
	Vec2D getRightNormal();

	bool operator == (Vec2D v2);
	bool operator != (Vec2D v2);
	Vec2D operator * (double k);
	Vec2D operator + (Vec2D v2);
	Vec2D operator - (Vec2D v2);

private:
	double x;
	double y;
};

