/*
 *  EventHandler.cpp
 *  Gravity
 *
 *  Created by Julian on 8/14/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "EventHandler.h"

EventHandler::EventHandler() {
	printf("Event handler constructed");
}

void EventHandler::mouseMoved(SDL_Event event) {
	printf("mouse moved triggered\n");
}

void EventHandler::mouseButton(SDL_Event event) {
	printf("mouse button triggered\n");
}