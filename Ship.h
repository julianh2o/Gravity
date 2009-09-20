/*
 *  Ship.h
 *  Gravity
 *
 *  Created by Julian on 8/19/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Ship_H
#define Ship_H

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif

#include "Inertial.h"
#include "Vector2D.h"
#include "Drawable.h"
#include "Functions.h"
#include "Part.h"
#include "Thruster.h"
#include "Updatable.h"
#include "Capacitor.h"
#include "Generator.h"
#include "Radiator.h"
#include "EquipmentCollection.h"

class Ship : public Inertial, public Drawable, public Updatable {
private:
	double heading;
	bool dead;
	Thruster * thruster;
	Capacitor * capacitor;
	Generator * generator;
	Radiator * radiator;
	double energy;

	double thrusterHeat;
	bool thrusterOverheat;
	
	double generatorHeat;
	bool generatorOverheat;
	
	double flashCooling;
public:
	Ship();
	Ship(double x, double y);
	
	void updateMass();
	
	void draw();
	
	void equip(Part * p);
	void update(int loopDelta);

	void thrust(int delta);
	
	void kill();
	bool isDead();
	
	Thruster * getThruster();
	Capacitor * getCapacitor();
	Generator * getGenerator();
	Radiator * getRadiator();
	Part * getPart(EquipmentCollection::PartType type);
	
	void setHeading(double heading);
	double getHeading();
	void incHeading(double heading);
	
	double getEnergy();
	void setEnergy(double energy);
	void incEnergy(double energy);
	double getThrusterHeat();
	void setThrusterHeat(double thrusterHeat);
	void incThrusterHeat(double thrusterHeat);
	double getGeneratorHeat();
	void setGeneratorHeat(double generatorHeat);
	void incGeneratorHeat(double generatorHeat);
	double getFlashCooling();
	void setFlashCooling(double flashCooling);
	void incFlashCooling(double flashCooling);

	bool isThrusterOverheating();
	bool isGeneratorOverheating();
};

#endif