/*
 *  EventHandler.h
 *  Gravity
 *
 *  Created by Julian on 8/14/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef EventHandler_H
#define EventHandler_H

#include "SDL.h"

#include "MouseMotionListener.h"
#include "MouseButtonListener.h"

class EventHandler: public MouseMotionListener, public MouseButtonListener {
public:
	EventHandler();
	void mouseMoved(SDL_Event event);
	void mouseButton(SDL_Event event);
};

#endif