#include "System.h"
#include "Vec2D.h"
#include "PolygonUtils.h"

#include <iostream>

void applyVelocity(World* world, double dt)
{
	unsigned int entity;
	Position* p;
	Velocity* v;

	for (entity = 0; entity < ENTITY_COUNT; ++entity)
	{
		if ((world->mask[entity] & MOVEMENT_MASK) == MOVEMENT_MASK)
		{
			p = &(world->position[entity]);
			v = &(world->velocity[entity]);

			p->x += v->xv * dt;
			p->y += v->yv * dt;
		}
	}
}

void applyCollision(World* world, double dt)
{
	unsigned int entity1;
	Position* p1;
	Velocity* v1;
	Polygon* pol1;
	Physics* phys1;

	unsigned int entity2;
	Position* p2;
	Velocity* v2;
	Polygon* pol2;
	Physics* phys2;

	for (entity1 = 0; entity1 < ENTITY_COUNT; ++entity1)
	{
		if ((world->mask[entity1] & RIGID_BODY_MASK) == RIGID_BODY_MASK)
		{
			p1 = &(world->position[entity1]);
			pol1 = &(world->polygon[entity1]);

			for (entity2 = 0; entity2 < ENTITY_COUNT; ++entity2)
			{
				if ((world->mask[entity2] & RIGID_BODY_MASK) == RIGID_BODY_MASK && entity1 != entity2)
				{
					p2 = &(world->position[entity2]);
					pol2 = &(world->polygon[entity2]);
					
					Vec2D mtv = getMtv(&getPolygonAt(pol1, p1), &getPolygonAt(pol2, p2));
					Vec2D basis = mtv.getUnitVector();

					double overlap = mtv.getMagnitude();

					if (mtv != Vec2D(0, 0))
					{
						v1 = &(world->velocity[entity1]);
						phys1 = &(world->physics[entity1]);
						
						v2 = &(world->velocity[entity2]);
						phys2 = &(world->physics[entity2]);

						Vec2D velDiff = Vec2D(v2->xv, v2->yv) - Vec2D(v1->xv, v1->yv);
						double velAlongNormal = velDiff.dotProduct(basis);

						if (velAlongNormal > 0)
						{
							double e = std::min(phys1->e, phys2->e);
							double impuleMagnitude = (-(1 + e) * velAlongNormal) / (phys1->invMass + phys2->invMass);

							Vec2D impulse = basis * impuleMagnitude;

							v1->xv -= phys1->invMass * impulse.getX();
							v1->yv -= phys1->invMass * impulse.getY();

							v2->xv += phys2->invMass * impulse.getX();
							v2->yv += phys2->invMass * impulse.getY();
						}

						double percent = 0.8; // usually 20% to 80%
						double slop = 0.01; // usually 0.01 to 0.1
						double magnitude = (std::max(overlap - slop, 0.0) / (phys1->invMass + phys2->invMass)) * percent;

						Vec2D correction = basis * magnitude;
						Vec2D correction1 = correction * phys1->invMass;
						Vec2D correction2 = correction * -phys2->invMass;

						p1->x += correction1.getX();
						p1->y += correction1.getY();

						p2->x += correction2.getX();
						p2->y += correction2.getY();

					}
				}
			}
		}
	}
}


std::vector<void (*)(World*, double dt)> systems = { applyVelocity, applyCollision };
