/*
 *  Particle.h
 *  Gravity
 *
 *  Created by Julian on 9/15/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Particle_H
#define Particle_H

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif

#include "Inertial.h"
#include "Vector2D.h"
#include "Drawable.h"
#include "Updatable.h"
#include "Functions.h"

class Particle : public Inertial, public Drawable, public Updatable {
	bool dead;
public:
	Particle();
	void draw();
	void update(int delta);
	bool isDead();
	void kill();
};


#endif