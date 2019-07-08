// EntityComponentSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "EntityFactory.h"
#include "System.h"
#include "InputSystem.h"
#include "RenderSystem.h"

#define TPS 60


void gameLoop(World* world, SDL_Renderer* renderer)
{
	bool running = true;
	double T = 1000 / TPS;
	while (running)
	{
		SDL_Event ev;
		while (SDL_PollEvent(&ev) != 0)
		{
			if (ev.type == SDL_QUIT) {
				running = false;
			}
		}

		for (int s = 0; s < inputSystems.size(); s++) inputSystems[s](world, T);
		for (int s = 0; s < systems.size(); s++) systems[s](world, T);
		for (int s = 0; s < renderSystems.size(); s++) renderSystems[s](world, renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(T);
	}

}

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);



	World* world = new World();

	createMovingTriangle(world, 100, { 0, 200.0 });
	createBackground(world, { 255, 255, 255, 255 });

	gameLoop(world, renderer);

	

	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
