#include "RenderSystem.h"

void drawBackground(World* world, SDL_Renderer* renderer)
{
	unsigned int entity;
	Colour colour;
	for (entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if ((world->mask[entity] & DRAW_BACKGROUND_MASK) == DRAW_BACKGROUND_MASK)
		{
			colour = world->colour[entity];

			SDL_SetRenderDrawColor(renderer, colour.r, colour.g , colour.b, colour.a);
			SDL_RenderClear(renderer);
		}
	}

}

void drawPolygons(World* world, SDL_Renderer* renderer)
{
	unsigned int entity;
	Position* position;
	Polygon* polygon;

	Colour colour;

	for (entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if ((world->mask[entity] & DRAW_POLYGON_MASK) == DRAW_POLYGON_MASK)
		{
			position = &(world->position[entity]);
			polygon = &(world->polygon[entity]);
			colour = world->colour[entity];

			renderPolygon(polygon, (int)position->x, (int)position->y, colour, renderer);
		}
	}
}



std::vector<void (*)(World*, SDL_Renderer*)> renderSystems = { drawBackground, drawPolygons };
