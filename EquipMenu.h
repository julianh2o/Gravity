/*
 *  EquipMenu.h
 *  Gravity
 *
 *  Created by Julian on 8/24/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef EquipMenu_H
#define EquipMenu_H

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif

#include "Drawable.h"
#include "Updatable.h"
#include "Functions.h"
#include "Part.h"
#include "EquipmentCollection.h"
#include "Ship.h"
#include "Radiator.h"
#include "Generator.h"

class EquipMenu : public Drawable, public Updatable {
private:
	Ship * ship;
	EquipmentCollection * eq;
	std::vector<int> targetX;
	int targetY;
	std::vector<double> offsetX;
	double offsetY;
public:
	EquipMenu(EquipmentCollection * eq, Ship * ship);
	
	void draw();
	void update(int delta);

	void left();
	void right();
	void up();
	void down();
};

#endif