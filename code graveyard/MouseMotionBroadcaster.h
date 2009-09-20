/*
 *  MouseMotionBroadcaster.h
 *  Gravity
 *
 *  Created by Julian on 8/14/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef MouseMotionBroadcaster_H
#define MouseMotionBroadcaster_H

#include "SDL.h"
#include <vector>

#include "MouseMotionListener.h"

class MouseMotionBroadcaster {
	std::vector<MouseMotionListener*> listeners;
public:
	MouseMotionBroadcaster();
	void raiseEvent(SDL_Event event);
	void addListener(MouseMotionListener* listener);
	void removeListener(MouseMotionListener* listener);
};

#endif