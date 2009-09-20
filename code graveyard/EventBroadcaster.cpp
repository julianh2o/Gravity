/*
 *  EventBroadcaster.cpp
 *  Gravity
 *
 *  Created by Julian on 8/15/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "EventBroadcaster.h"


template <class T>EventBroadcaster::EventBroadcaster() {
	
}
/*
void EventBroadcaster::raiseEvent(SDL_Event event) {
	for (int i=0; i<listeners.size(); i++) {
		listeners[i]->eventRaised(event);
	}
}

void EventBroadcaster::addListener(EventListener* listener) {
	listeners.push_back(listener);
}

void EventBroadcaster::removeListener(EventListener* listener) {
	for (int i=0; i<listeners.size(); i++) {
		if (listener == listeners[i]) {
			listeners.erase(listeners.begin()+i);
			return;
		}
	}
}*/