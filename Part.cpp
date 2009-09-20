/*
 *  Part.cpp
 *  Gravity
 *
 *  Created by Julian on 8/21/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Part.h"

Part::Part() {
	this->mass = 1;
}

Part::Part(double mass) {
	this->mass = mass;
}

double Part::getMass() {
	return mass;
}

void Part::setMass(double mass) {
	this->mass = mass;
}