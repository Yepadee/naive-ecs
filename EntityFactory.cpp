#include "EntityFactory.h"

unsigned int createEntity(World* world)
{
	unsigned int entity;
	for (entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if (world->mask[entity] == COMPONENT_NONE)
		{
			return(entity);
		}
	}

	printf("Error!  No more entities left!\n");
	return(ENTITY_COUNT);
}

void destroyEntity(World* world, unsigned int entity)
{
	world->mask[entity] = COMPONENT_NONE;
}

unsigned int createBackground(World* world, Colour c)
{
	unsigned int entity = createEntity(world);

	world->mask[entity] = DRAW_BACKGROUND_MASK;
	world->colour[entity] = c;

	return entity;
}

unsigned int createTriangle(World* world, double radius, Position p)
{
	unsigned int entity = createEntity(world);


	world->mask[entity] = COMPONENT_POSITION
						| COMPONENT_VELOCITY
						| COMPONENT_COLOUR
						| COMPONENT_POLYGON
						| COMPONENT_MOUSE_DRAG
						| COMPONENT_PHYSICS;


	world->position[entity] = p;

	world->velocity[entity] = { 0, 0 };

	world->polygon[entity] = newRegularPolygon(3, radius);
	world->colour[entity] = {255, 0, 0, 255};

	world->mouseDrag[entity] = { 0, 0, false };

	world->physics[entity].e = 1.0;
	world->physics[entity].mass = 5.0;
	world->physics[entity].invMass = 1.0 / world->physics[entity].mass;

	return entity;
}

unsigned int createMovingTriangle(World* world, double radius, Position p)
{
	unsigned int entity = createEntity(world);


	world->mask[entity] = COMPONENT_POSITION
		| COMPONENT_VELOCITY
		| COMPONENT_COLOUR
		| COMPONENT_POLYGON
		| COMPONENT_MOUSE_DRAG
		| COMPONENT_PHYSICS;


	world->position[entity] = p;

	world->velocity[entity] = { 0.5, 0 };

	world->polygon[entity] = newRegularPolygon(3, radius);
	world->colour[entity] = { 255, 0, 0, 255 };

	world->mouseDrag[entity] = { 0, 0, false };

	world->physics[entity].e = 1.0;
	world->physics[entity].mass = 5.0;
	world->physics[entity].invMass = 1.0 / world->physics[entity].mass;

	return entity;
}