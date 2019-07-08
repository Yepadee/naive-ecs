#pragma once

#include "PolygonUtils.h"

#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H


unsigned int createEntity(World* world);

void destroyEntity(World* world, unsigned int entity);


unsigned int createBackground(World* world, Colour c);
unsigned int createTriangle(World* world, double radius, Position p);
unsigned int createMovingTriangle(World* world, double radius, Position p);

#endif 