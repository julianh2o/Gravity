/*
 *  Gravity.h
 *  Gravity
 *
 *  Created by Julian on 8/16/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Gravity_H
#define Gravity_H

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif


#include "math.h"
#include <vector>

#include "Functions.h"
#include "Vector2D.h"
#include "Planet.h"
#include "Inertial.h"
#include "KeyState.h"
#include "KeyBinding.h"
#include "Constants.h"
#include "Ship.h"
#include "View.h"
#include "Projectile.h"
#include "Thruster.h"
#include "EquipMenu.h"
#include "Color.h"
#include "Particle.h"

class Gravity {
private:
	bool paused;
	bool fullscreen;
	int reloadTime;
	int mouseX, mouseY;
	KeyBinding *k;
	View *v;
	Ship *ship;
	EquipMenu * menu;
	std::vector<Ship*> enemies;
	std::vector<Planet*> planets;
	std::vector<Projectile*> projectiles;
	std::vector<Particle*> particles;
	
	EquipmentCollection * eq;
public:
	Gravity();
	void update(int delta);
	void draw();
	void mouseMoved(SDL_Event event);
	void mouseButton(SDL_Event event);
	void keyUp(SDL_Event event);
	void keyDown(SDL_Event event);
	void drawPrediction(Inertial * target);
};

#endif