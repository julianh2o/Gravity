/*
 *  KeyBinding.cpp
 *  Gravity
 *
 *  Created by Julian on 8/18/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

// This class manages keybindings, bind() is called with a name for the binding
// and the SDLKey to be associated with it. check() uses the given KeyState object
// to return a boolean based on the state of the keyboard.

#include "KeyBinding.h"

KeyBinding::KeyBinding() {
}

// binds a string name to a SDLKey
void KeyBinding::bind(std::string s, SDLKey k) {
	keys[s] = k;
}

void KeyBinding::unbind(std::string s) {
	keys.erase(s);
}

// Returns the state of the keyboard according to the given keystate
bool KeyBinding::check(std::string s) {
	if (keys.find(s) != keys.end()) {
		return keyDown(keys[s]);
	}
}

bool KeyBinding::check(std::string s, SDL_Event event) {
	if (keys.find(s) != keys.end()) {
		return event.key.keysym.sym == keys[s];
	}
}