#pragma once

#include "SDL.h"
#include "Component.h"
#include <algorithm>

#include "Vec2D.h"

#ifndef POLYGON_UTILS_H
#define POLYGON_UTILS_H
//Utils
static double minElement(std::vector<double> xs);

static double maxElement(std::vector<double> xs);


//Properties
double getArea(Polygon* p);

Position getCentroid(Polygon* p);


//Movement
Polygon getPolygonAt(Polygon* p, Position* pos);

void rotatePolygon(Polygon* p, double angle);


//Collision
bool insidePolygon(int x, int y, Polygon* p);

SDL_Rect getAABB(Polygon* p);

bool aabbCollision(Polygon* p1, Polygon* p2);

Vec2D getMtv(Polygon* p1, Polygon* p2);


//Rendering
static std::vector<int> getDrawList(Polygon* p, int y);

void renderPolygon(Polygon* p, int px, int py, SDL_Color c, SDL_Renderer* renderer);


//Creation
Polygon newRegularPolygon(int numVertices, double radius);

#endif