/*
 *  Ship.cpp
 *  Gravity
 *
 *  Created by Julian on 8/19/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Ship.h"

Ship::Ship() {
	set(0,0);
	setMass(1);
	dead = false;
	thrusterHeat = 0;
	thrusterOverheat = false;
	energy = 0;
}

Ship::Ship(double x, double y) {
	set(x,y);
	setMass(1);
	dead = false;
	thrusterHeat = 0;
	thrusterOverheat = false;
	energy = 0;
}

void Ship::updateMass() {
	double mass = 1;
	if (thruster) mass += thruster->getMass();
	if (capacitor) mass += capacitor->getMass();
	if (generator) mass += generator->getMass();
	setMass(mass);
}

void Ship::draw() {
	Vector2D pos = Vector2D(getX(),getY());
	int tipSize = 10;
	int backSize = 5;
	Vector2D tip = pos + Vector2D(getHeading())*tipSize;
	Vector2D back = pos - Vector2D(getHeading())*backSize;
	int wingSize = 5;
	Vector2D rWing = back + Vector2D(getHeading()+M_PI/2)*wingSize;
	Vector2D lWing = back + Vector2D(getHeading()-M_PI/2)*wingSize;
	
	glColor3f(1.,1.,1.);
	if (thrusterOverheat) glColor3f(1.,0.,0.);
	glBegin(GL_POLYGON);
	gvi(tip);
	gvi(lWing);
	gvi(rWing);
	glEnd();
}

void Ship::equip(Part * part) {
	Thruster * t = dynamic_cast<Thruster*>(part);
	if (t) {
		thruster = t;
	}
	
	Capacitor * c = dynamic_cast<Capacitor*>(part);
	if (c) {
		capacitor = c;
		energy = capacitor->getCapacity();
	}
	
	Generator * g = dynamic_cast<Generator*>(part);
	if (g) {
		generator = g;
	}
	
	Radiator * r = dynamic_cast<Radiator*>(part);
	if (r) {
		radiator = r;
	}
	updateMass();
}

void Ship::update(int delta) {
	updatePos(delta);
	
	if (energy < capacitor->getCapacity() && !generatorOverheat) {
		incEnergy(pps(generator->getEnergyOutput(),delta));
		incGeneratorHeat(pps(generator->getUsageHeat(),delta));
	}

	if (energy > capacitor->getCapacity()) {
		incEnergy(-pps(capacitor->getOverchargeLeak(),delta));
	}

	if (thrusterHeat > 0) {
		incThrusterHeat(-pps(thruster->getCoolingRate(),delta));
		incThrusterHeat(-pps(radiator->getSystemCoolingRate(),delta));
	}
	
	if (generatorHeat > 0) {
		incGeneratorHeat(-pps(generator->getCoolingRate(),delta));
		incGeneratorHeat(-pps(radiator->getSystemCoolingRate(),delta));
	}
	
	double fcpu = pps(radiator->getFlashCoolingRate(),delta);
	if (fcpu > flashCooling) fcpu = flashCooling;
	if (fcpu > 0 && generatorHeat > 0) {
		double remains = fcpu - generatorHeat;
		if (remains > 0) fcpu = remains;
		incGeneratorHeat(-fcpu);
		incFlashCooling(-fcpu);
	}
	if (fcpu > 0 && thrusterHeat > 0) {
		incThrusterHeat(-fcpu);
		incFlashCooling(-fcpu);
	}

	incFlashCooling(pps(radiator->getFlashCoolingRecharge(),delta));
}

void Ship::thrust(int delta) {
	if (energy > pps(thruster->getUsageDrain(),delta) && !thrusterOverheat) {
		Vector2D dir = Vector2D(heading);
		dir *= pps(thruster->getThrust(),delta);
		incVel(dir);
		energy -= pps(thruster->getUsageDrain(),delta);
		thrusterHeat += pps(thruster->getUsageHeat(),delta);
		if (thrusterHeat >= thruster->getHeatCapacity()) thrusterOverheat = true;
	}
}

void Ship::kill() {
	dead = true;
}

bool Ship::isDead() {
	return dead;
}

Thruster * Ship::getThruster() {
	return thruster;
}

Capacitor * Ship::getCapacitor() {
	return capacitor;
}

Generator * Ship::getGenerator() {
	return generator;
}

Radiator * Ship::getRadiator() {
	return radiator;
}

Part * Ship::getPart(EquipmentCollection::PartType type) {
	switch (type) {
		case EquipmentCollection::THRUSTER:
			return getThruster();
		case EquipmentCollection::CAPACITOR:
			return getCapacitor();
		case EquipmentCollection::GENERATOR:
			return getGenerator();
		case EquipmentCollection::RADIATOR:
			return getRadiator();
	}
	return NULL;
}

void Ship::setHeading(double heading) {
	this->heading = heading;
}

double Ship::getHeading() {
	return heading;
}

void Ship::incHeading(double heading) {
	this->heading += heading;
}

double Ship::getEnergy() {
	return energy;
}

void Ship::setEnergy(double energy) {
	if (energy > capacitor->getCapacity()) energy = capacitor->getCapacity();
	if (energy < 0) energy = 0;
	this->energy = energy;
}

void Ship::incEnergy(double energy) {
	setEnergy(getEnergy() + energy);
}

double Ship::getThrusterHeat() {
	return thrusterHeat;
}

void Ship::setThrusterHeat(double thrusterHeat) {
	if (thrusterHeat > thruster->getHeatCapacity()) {
		thrusterHeat = thruster->getHeatCapacity();
		thrusterOverheat = true;
	}
	if (thrusterHeat <= 0) {
		thrusterHeat = 0;
		thrusterOverheat = false;
	}
	this->thrusterHeat = thrusterHeat;
}

void Ship::incThrusterHeat(double thrusterHeat) {
	setThrusterHeat(getThrusterHeat() + thrusterHeat);
}

double Ship::getGeneratorHeat() {
	return generatorHeat;
}

void Ship::setGeneratorHeat(double generatorHeat) {
	if (generatorHeat > generator->getHeatCapacity()) {
		generatorHeat = generator->getHeatCapacity();
		generatorOverheat = true;
	}
	if (generatorHeat <= 0) {
		generatorHeat = 0;
		generatorOverheat = false;
	}
	this->generatorHeat = generatorHeat;
}

void Ship::incGeneratorHeat(double generatorHeat) {
	setGeneratorHeat(getGeneratorHeat() + generatorHeat);
}

double Ship::getFlashCooling() {
	return flashCooling;
}

void Ship::setFlashCooling(double flashCooling) {
	if (flashCooling > radiator->getFlashCoolingCapacity()) flashCooling = radiator->getFlashCoolingCapacity();
	if (flashCooling < 0) flashCooling = 0;
	this->flashCooling = flashCooling;
}

void Ship::incFlashCooling(double flashCooling) {
	setFlashCooling(getFlashCooling() + flashCooling);
}

bool Ship::isThrusterOverheating() {
	return thrusterOverheat;
}

bool Ship::isGeneratorOverheating() {
	return generatorOverheat;
}