/*
 *  Particle.cpp
 *  Gravity
 *
 *  Created by Julian on 9/15/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Particle.h"

Particle::Particle() {
	dead = false;
}

void Particle::draw() {
	glBegin(GL_POLYGON);
	int size = (int)getMass();
	if (size < 2) size = 2;
	rect(getX(),getY(),getX()+size,getY()+size);
	glEnd();
}

void Particle::update(int delta) {
	updatePos(delta);
}

bool Particle::isDead() {
	return dead;
}

void Particle::kill() {
	dead = true;
}