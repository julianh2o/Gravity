/*
 *  Planet.h
 *  Gravity
 *
 *  Created by Julian on 8/18/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Planet_H
#define Planet_H

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif

#include "Updatable.h"
#include "Drawable.h"
#include "Vector2D.h"
#include "Functions.h"
#include "Inertial.h"
#include "Constants.h"

class Planet : public Updatable, public Drawable {
private:
	Vector2D pos;
	double mass;
	double radius;
public:
	Planet();
	Planet(double x, double y, double mass, double radius);
	
	void update(int delta);
	void draw();
	void affect(Inertial * a, int delta);
	
	double distanceTo(Inertial * a);

	const Vector2D getPos();
	double getX();
	void setX(double x);
	double getY();
	void setY(double y);
	double getMass();
	void setMass(double mass);
	double getRadius();
	void setRadius(double radius);
};

#endif