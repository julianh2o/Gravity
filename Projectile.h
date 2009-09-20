/*
 *  Projectile.h
 *  Gravity
 *
 *  Created by Julian on 8/20/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Projectile_H
#define Projectile_H

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif

#include <vector>

#include "Vector2D.h"
#include "Inertial.h"
#include "Drawable.h"
#include "Updatable.h"
#include "Functions.h"

class Projectile : public Inertial, public Drawable, public Updatable {
private:
	int life;
	std::vector<Vector2D> tail;
	double heading;
public:
	int targetEnemy;
	Projectile();
	Projectile(const Vector2D &pos, const Vector2D &vel);

	void update(int delta);
	void draw();

	void kill();
	bool isDead();
	int getLife();
	void setLife(int life);
	
	void thrust(double force);
	
	void setHeading(double heading);
	double getHeading();
	void incHeading(double heading);
};

#endif