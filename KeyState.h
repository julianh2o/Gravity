/*
 *  KeyState.h
 *  Gravity
 *
 *  Created by Julian on 8/18/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "SDL.h"

#include <map>

#ifndef KeyState_H
#define KeyState_H

class KeyState {
private:
	struct intcmp {
		bool operator()(const int a, const int b) {
			return a<b;
		}
	};
	
	std::map<Uint8,bool,intcmp> keyMap;
public:
	KeyState();
	void handleKeyEvent(SDL_Event e);
	void handleMouseEvent(SDL_Event e);
	bool keyDown(SDLKey key);
	bool keyDown(SDLKey key, SDLKey key2);
};

#endif