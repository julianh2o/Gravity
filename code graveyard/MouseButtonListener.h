/*
 *  MouseButtonListener.h
 *  Gravity
 *
 *  Created by Julian on 8/15/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef MouseButtonListener_H
#define MouseButtonListener_H

#include "SDL.h"

class MouseButtonListener {
public:
	virtual void mouseButton(SDL_Event event) {};
};

#endif