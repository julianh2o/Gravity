/*
 *  MouseMotionBroadcaster.cpp
 *  Gravity
 *
 *  Created by Julian on 8/14/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "MouseMotionBroadcaster.h"

MouseMotionBroadcaster::MouseMotionBroadcaster() {
	
}

void MouseMotionBroadcaster::raiseEvent(SDL_Event event) {
	for (int i=0; i<listeners.size(); i++) {
		listeners[i]->mouseMoved(event);
	}
}

void MouseMotionBroadcaster::addListener(MouseMotionListener* listener) {
	listeners.push_back(listener);
}

void MouseMotionBroadcaster::removeListener(MouseMotionListener* listener) {
	for (int i=0; i<listeners.size(); i++) {
		if (listener == listeners[i]) {
			listeners.erase(listeners.begin()+i);
			return;
		}
	}
}