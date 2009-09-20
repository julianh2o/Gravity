/*
 *  EventBroadcaster.h
 *  Gravity
 *
 *  Created by Julian on 8/15/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef EventBroadcaster_H
#define EventBroadcaster_H

#include "SDL.h"

#include <vector>

#include "EventListener.h"

template <class T> class EventBroadcaster {
	std::vector<T*> listeners;
public:
	EventBroadcaster();
//	void raiseEvent(SDL_Event event);
//	void addListener(T* listener);
//	void removeListener(T* listener);
};

#endif