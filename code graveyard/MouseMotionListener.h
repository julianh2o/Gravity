/*
 *  MouseMotionListener.h
 *  Gravity
 *
 *  Created by Julian on 8/14/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef MouseMotionListener_H
#define MouseMotionListener_H

#include "SDL.h"

class MouseMotionListener {
public:
	virtual void mouseMoved(SDL_Event event) {};
};

#endif