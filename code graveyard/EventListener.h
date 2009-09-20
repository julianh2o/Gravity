/*
 *  EventListener.h
 *  Gravity
 *
 *  Created by Julian on 8/15/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef EventListener_H
#define EventListener_H

#include "SDL.h"

class EventListener {
public:
	virtual void eventRaised(SDL_Event event) {};
};

#endif