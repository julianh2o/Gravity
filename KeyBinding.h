/*
 *  KeyBinding.h
 *  Gravity
 *
 *  Created by Julian on 8/18/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef KeyBinding_H
#define KeyBinding_H

#include "SDL.h"

#include <string>
#include <map>

#include "KeyState.h"

class KeyBinding : public KeyState {
	std::map<std::string,SDLKey> keys;
public:
	KeyBinding();
	void bind(std::string s, SDLKey k);
	void unbind(std::string s);
	bool check(std::string s);
	bool check(std::string s, SDL_Event event);
};

#endif