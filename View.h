/*
 *  View.h
 *  Gravity
 *
 *  Created by Julian on 8/19/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef View_H
#define View_H

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif

#include "Inertial.h"
#include "Updatable.h"
#include "Functions.h"
#include "Vector2D.h"

class View : public Inertial, public Updatable {
private:
	double target;
	double current;
	Vector2D size;
	Vector2D mouse;
public:
	View();
	View(double x, double y);
	void setMouse(int x, int y);
	Vector2D getMouse();
	void zoomIn();
	void zoomOut();
	void update(int delta);
	
	void applyGUI();
	void apply();
};

#endif