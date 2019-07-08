#pragma once

#include "SDL.h"

#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

typedef struct {
	int x, y; //Mouse's x and y position.
	bool moving; //Whether the mouse is moving.
	bool buttons[4]; //The current state of the mouse buttons.
	bool lastButtons[4]; //The state of the mouse buttons from the previous tick.
} MouseInput;

bool mousePressed(int mouseButton);
bool mouseReleased(int mouseButton);
bool mouseDown(int mouseButton);
bool mouseMoving();
void updateMouse(SDL_Event ev);

int mouseX();
int mouseY();

#endif