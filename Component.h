#include <string>
#include <vector>

#include "SDL.h"

#ifndef COMPONENT_H
#define COMPONENT_H


#define ENTITY_COUNT 100

#define MOVEMENT_MASK (COMPONENT_POSITION | COMPONENT_VELOCITY)

#define DRAW_BACKGROUND_MASK (COMPONENT_COLOUR | COMPONENT_BACKGROUND)
#define DRAW_POLYGON_MASK (COMPONENT_POSITION | COMPONENT_POLYGON | COMPONENT_COLOUR)

#define RIGID_BODY_MASK (MOVEMENT_MASK | COMPONENT_PHYSICS | COMPONENT_POLYGON)

#define DRAG_INPUT_MASK (COMPONENT_MOUSE_DRAG | COMPONENT_POSITION | COMPONENT_POLYGON)

typedef enum
{
	COMPONENT_NONE = 0,

	COMPONENT_POSITION = 1 << 0,
	COMPONENT_VELOCITY = 1 << 1,
	COMPONENT_APPEARANCE = 1 << 2,
	COMPONENT_COLOUR = 1 << 3,
	COMPONENT_POLYGON = 1 << 4,
	COMPONENT_PHYSICS = 1 << 5,
	COMPONENT_MOUSE_DRAG = 1 << 6,
	COMPONENT_BACKGROUND = 1 << 7
} Component;


typedef struct
{
	double x;
	double y;
} Position;

typedef struct
{
	double xv;
	double yv;
} Velocity;

typedef struct
{
	std::string name;
} Appearance;

typedef struct {
	int numVertices;
	std::vector<double> xs;
	std::vector<double> ys;
} Polygon;

typedef struct {
	double mass;
	double invMass;
	double e;

} Physics;

typedef struct
{
	int xDist;
	int yDist;
	bool canDrag;
} MouseDrag;

typedef SDL_Color Colour;

typedef struct
{
	int mask[ENTITY_COUNT];

	Position position[ENTITY_COUNT];
	Velocity velocity[ENTITY_COUNT];
	Appearance appearance[ENTITY_COUNT];
	Colour colour[ENTITY_COUNT];
	Polygon polygon[ENTITY_COUNT];
	Physics physics[ENTITY_COUNT];
	MouseDrag mouseDrag[ENTITY_COUNT];

} World;

#endif