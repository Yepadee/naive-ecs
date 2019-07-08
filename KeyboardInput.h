#pragma once

#include "SDL.h"

#ifndef KEY_INPUT_H
#define KEY_INPUT_H

typedef struct {
	Uint8 keys[128];
	Uint8 lastKeys[128];
} KeyInput;

bool keyPressed(int key);
bool keyReleased(int key);
bool keyDown(int key);

void updateKeyboard();

#endif