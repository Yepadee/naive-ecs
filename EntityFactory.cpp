#include "EntityFactory.h"
#include <cstdlib>

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

static int randInt(int min, int max) {
	return (std::rand() % max) + min;
}

unsigned int createRandRigidBody(World* world, Position p)
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

	world->polygon[entity] = newRegularPolygon(randInt(3, 8), randInt(20, 80));
	world->colour[entity] = { (Uint8) randInt(0, 255), (Uint8) randInt(0, 255), (Uint8) randInt(0, 255), 255 };

	world->mouseDrag[entity] = { 0, 0, false };

	world->physics[entity].e = (double) randInt(0, 100) / 100.0;

	world->physics[entity].mass = randInt(1, 10);
	world->physics[entity].invMass = 1.0 / world->physics[entity].mass;

	return entity;
}