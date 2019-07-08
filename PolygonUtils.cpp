#include "PolygonUtils.h"

#include <iostream>

#define PI 3.14159265358979323846


//Utils
static double minElement(std::vector<double> xs) {
	return *std::min_element(xs.begin(), xs.end());
}

static double maxElement(std::vector<double> xs) {
	return *std::max_element(xs.begin(), xs.end());
}


//Properties
double getArea(Polygon* p)
{
	double area = 0;
	int j = p->numVertices - 1;
	for (int i = 0; i < p->numVertices; i++) {
		double x1 = p->xs[i];
		double x2 = p->xs[j];
		double y1 = p->ys[i];
		double y2 = p->ys[j];
		j = i;
		area += (x1 + x2) * (y1 - y2);
	}
	return area / 2;
}

Position getCentroid(Polygon* p)
{
	double xSum = 0;
	double ySum = 0;
	int j = p->numVertices - 1;
	for (int i = 0; i < p->numVertices; i++) {
		double x1 = p->xs[i];
		double x2 = p->xs[j];
		double y1 = p->ys[i];
		double y2 = p->ys[j];
		xSum += ((x1 + x2) * (x1 * y2 - x2 * y1));
		ySum += ((y1 + y2) * (x1 * y2 - x2 * y1));
		j = i;
	}
	double area = 6 * getArea(p);
	double divisor = 6 * area;
	Position centroid = { xSum / divisor, ySum / divisor };
	return centroid;
}


//Movement
static void movePolygon(Polygon* p, double dx, double dy) {
	for (int i = 0; i < p->numVertices; i++) {
		p->xs[i] += dx;
		p->ys[i] += dy;
	}
}

Polygon getPolygonAt(Polygon* p, Position* pos)
{
	std::vector<double> xs = p->xs;
	std::vector<double> ys = p->ys;

	for (int i = 0; i < p->numVertices; i++)
	{
		xs[i] += pos->x;
		ys[i] += pos->y;
	}

	Polygon result = { p->numVertices, xs, ys };
	return result;
}

void rotatePolygon(Polygon* p, double angle) {
	Position axis = getCentroid(p);
	movePolygon(p, axis.x, axis.y);
	for (int i = 0; i < p->numVertices; i++) {
		double x = p->xs[i];
		double y = p->ys[i];
		p->xs[i] = x * cos(angle) - y * sin(angle);
		p->ys[i] = y * cos(angle) + x * sin(angle);
	}
	movePolygon(p, axis.x * -1, axis.y * -1);
}


//Collision
static int isLeft(int x, int y, int ax, int ay, int bx, int by) {
	//> 0 for (x,y) left of the line through a to b
	//= 0 for (x,y) on the line
	//< 0 for (x,y) right of the line
	return ((bx - ax) * (y - ay) - (x - ax) * (by - ay));
}

bool insidePolygon(int x, int y, Polygon* p) {
	//Method to test a vertex lies within a polygon by use of winding number method [2]
	//The general theory is that if a point lies outside the polygon, then the winding number of the polygon around that point is 0;
	//So we calculate the polygons winding number around the test point.
	//The algorithm is sped up by only looking at the edges that are in line with the point. (the points y coord lies between the edges vertices y coords).
	int wn = 0;
	int j = p->numVertices - 1;
	for (int i = 0; i < p->numVertices; i++) { //Iterate over all the polygon's edges.
		//Record all the components of the vertices that make up an edge.
		int x1 = (int)p->xs[i];
		int y1 = (int)p->ys[i];
		int x2 = (int)p->xs[j];
		int y2 = (int)p->ys[j];
		if (y1 <= y) {
			if (y2 > y) {
				//If y lise between y1 and y2 with y2 above y1;
				if (isLeft(x, y, x1, y1, x2, y2) > 0) {
					//If the vertex is to the left of the upwards edge.
					wn++;
				}
			}
		}
		else if (y2 <= y) {
			//If y lise between y1 and y2 with y1 above y2;
			if (isLeft(x, y, x1, y1, x2, y2) < 0) {
				//If the vertex is to the right of the downwards edge.
				wn--;
			}
		}
		j = i;
	}
	return wn != 0;
}

SDL_Rect getAABB(Polygon* p)
{
	SDL_Rect aabb;
	aabb.x = (int)minElement(p->xs);
	aabb.y = (int)minElement(p->ys);
	aabb.w = (int)maxElement(p->xs) - aabb.x;
	aabb.h = (int)maxElement(p->xs) - aabb.y;

	return aabb;
}

bool aabbCollision(Polygon* p1, Polygon* p2) {
	SDL_Rect aabb1 = getAABB(p1);
	SDL_Rect aabb2 = getAABB(p2);
	return (aabb1.x + aabb1.w >= aabb2.x) && (aabb2.x + aabb2.w >= aabb1.x) &&
		(aabb1.y + aabb1.h >= aabb2.y) && (aabb2.y + aabb2.h >= aabb1.y);
}

static std::vector<Vec2D> getAxes1(Polygon* p)
{
	std::vector<Vec2D> axes = {};

	int j = p->numVertices - 1;
	for (int i = 0; i < p->numVertices; i++)
	{
		Vec2D v1(p->xs[i], p->ys[i]);
		Vec2D v2(p->xs[j], p->ys[j]);
		Vec2D dist = v2 - v1;
		axes.push_back(dist.getLeftNormal().getUnitVector());

		j = i;
	}

	return axes;
}

static std::vector<Vec2D> getAxes2(Polygon* p)
{
	std::vector<Vec2D> axes = {};

	int j = p->numVertices - 1;
	for (int i = 0; i < p->numVertices; i++)
	{
		Vec2D v1(p->xs[i], p->ys[i]);
		Vec2D v2(p->xs[j], p->ys[j]);
		Vec2D dist = v2 - v1;
		axes.push_back(dist.getRightNormal().getUnitVector());

		j = i;
	}

	return axes;
}

static Vec2D project(Vec2D axis, Polygon* p)
{
	Vec2D v0(p->xs[0], p->ys[0]);
	double min = v0.dotProduct(axis);
	double max = min;

	for (int i = 0; i < p->numVertices; i++)
	{
		Vec2D v(p->xs[i], p->ys[i]);
		double dp = v.dotProduct(axis);

		if (dp < min)
		{
			min = dp;
		}
		else if (dp > max)
		{
			max = dp;
		}
	}

	return Vec2D(min, max);

}

static bool overlaps(Vec2D projA, Vec2D projB)
{
	return (projA.getX() <= projB.getY() && projB.getX() <= projA.getY());
}

static double getOverlap(Vec2D projA, Vec2D projB)
{
	return abs(projB.getY() - projA.getX());
}

Vec2D getMtv(Polygon* p1, Polygon* p2)
{
	bool colliding = aabbCollision(p1, p2);

	double minOverlap = DBL_MAX;

	Vec2D smallestAxis = Vec2D(0, 0);
	std::vector<Vec2D> axes1 = getAxes1(p1);
	std::vector<Vec2D> axes2 = getAxes2(p2);

	for (int i = 0; i < axes1.size() && colliding; i++)
	{
		Vec2D axis = axes1[i];

		Vec2D proj1 = project(axis, p1);
		Vec2D proj2 = project(axis, p2);

		if (overlaps(proj1, proj2))
		{
			double overlap = getOverlap(proj1, proj2);
			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				smallestAxis = axis;
			}
		}
		else
		{
			colliding = false;
		}
	}

	for (int i = 0; i < axes2.size() && colliding; i++)
	{
		Vec2D axis = axes2[i];

		Vec2D proj1 = project(axis, p1);
		Vec2D proj2 = project(axis, p2);

		if (overlaps(proj1, proj2))
		{
			double overlap = getOverlap(proj1, proj2);
			if (overlap < minOverlap)
			{
				minOverlap = overlap;
				smallestAxis = axis;
			}
		}
		else
		{
			colliding = false;
		}
	}

	Vec2D mtv(0, 0);
	if (colliding) mtv = smallestAxis * minOverlap;

	return mtv;
}

//Rendering
static std::vector<int> getDrawList(Polygon* p, int y)
{
	std::vector<double> xs = p->xs;
	std::vector<double> ys = p->ys;

	std::vector<int> drawList = {};


	int j = p->numVertices - 1;
	for (int i = 0; i < p->numVertices; i++)
	{
		if (ys[i] < y && ys[j] >= y || ys[j] < y && ys[i] >= y)
		{
			//If the line through y intercects the edge, then record the the x coordinate of the intercept.
			int x = (int)(xs[i] + (y - ys[i]) / (ys[j] - ys[i]) * (xs[j] - xs[i]));
			drawList.push_back(x);
		}
		j = i;
	}

	return drawList;
}

void renderPolygon(Polygon* p, int px, int py, SDL_Color c, SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	int startY = (int)minElement(p->ys);
	int endY = (int)maxElement(p->ys);

	for (int y = startY; y <= endY; y++)
	{
		std::vector<int> drawList = getDrawList(p, y);
		if (drawList.size() > 1)
		{
			for (int i = 0; i < drawList.size() - 1; i += 2)
			{
				int j = i + 1;
				int startX = drawList[i];
				int endX = drawList[j];
				SDL_RenderDrawLine(renderer, px + startX, py + y, px + endX, py + y);
			}
		}

	}
}


//Creation
Polygon newRegularPolygon(int numVertices, double radius) {
	std::vector<double> xs = {};
	std::vector<double> ys = {};

	double angle = (2 * PI) / (double)numVertices;
	bool oddSides = (numVertices % 2 != 0);
	for (int i = 0; i < numVertices; i++) {
		double k = oddSides ? (double)i - 0.25 : (double)i + 0.5;
		double x = radius * cos(angle * k);
		double y = radius * sin(angle * k);
		xs.push_back(x);
		ys.push_back(y);
	}

	Polygon newPolygon = { numVertices, xs, ys };
	return newPolygon;
}