/*
 *  KeyState.cpp
 *  Gravity
 *
 *  Created by Julian on 8/18/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "KeyState.h"

KeyState::KeyState() {
	
}

void KeyState::handleKeyEvent(SDL_Event e) {
	keyMap[e.key.keysym.sym] = (e.type == SDL_KEYDOWN);
}

void KeyState::handleMouseEvent(SDL_Event e) {
	keyMap[e.button.button] = (e.type == SDL_MOUSEBUTTONDOWN);
}

bool KeyState::keyDown(SDLKey key) {
	return keyMap[key];
}

bool KeyState::keyDown(SDLKey key, SDLKey key2) {
	return keyMap[key] || keyMap[key2];
}

