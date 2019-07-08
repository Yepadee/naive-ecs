#include "InputSystem.h"

#include "EntityFactory.h"

#include <iostream>

void updateMouse(World* /*world*/, double /*dt*/)
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev) != 0);
	updateMouse(ev);
}

void updateKeys(World* /*world*/, double /*dt*/)
{
	updateKeyboard();
}

static bool touchingMouse(Polygon* polygon, Position* pos) {
	return insidePolygon(mouseX()- pos->x, mouseY() - pos->y, polygon);
}

void dragInput(World* world, double dt)
{
	unsigned int entity;
	Position* pos;
	MouseDrag* md;
	Polygon* polygon;

	bool touching = false;

	for (entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if ((world->mask[entity] & DRAG_INPUT_MASK) == DRAG_INPUT_MASK)
		{
			pos = &(world->position[entity]);
			md = &(world->mouseDrag[entity]);
			polygon = &(world->polygon[entity]);

			if (mousePressed(SDL_BUTTON_LEFT) && touchingMouse(polygon, pos))
			{
				md->xDist = (double) mouseX() - pos->x;
				md->yDist = (double) mouseY() - pos->y;
				md->canDrag = true;

			}

			if (md->canDrag)
			{
				double initialX = pos->x;
				double initialY = pos->y;

				double finalX = (double) mouseX() - md->xDist;
				double finalY = (double) mouseY() - md->yDist;

				double dx = finalX - initialX;
				double dy = finalY - initialY;

				pos->x += dx;
				pos->y += dy;

				touching = true;
			}

			if (mouseReleased(SDL_BUTTON_LEFT))
			{
				md->canDrag = false;
			}

		}
	}

	if (mousePressed(SDL_BUTTON_LEFT) && !touching)
	{
		createRandRigidBody(world, { (double) mouseX(), (double) mouseY() });
	}

}


std::vector<void (*)(World*, double)> inputSystems = { updateMouse, updateKeys, dragInput};