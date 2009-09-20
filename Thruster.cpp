/*
 *  Thruster.cpp
 *  Gravity
 *
 *  Created by Julian on 8/21/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Thruster.h"

Thruster::Thruster(double thrust, double usageDrain, double usageHeat, double heatCapacity, double coolingRate, double mass) : Part(mass) {
	this->thrust = thrust;
	this->usageDrain = usageDrain;
	this->usageHeat = usageHeat;
	this->heatCapacity = heatCapacity;
	this->coolingRate = coolingRate;
}

void Thruster::a() {
	
}

std::vector<Attribute> Thruster::getAttributes() {
	std::vector<Attribute> attr = std::vector<Attribute>();
	attr.push_back(Attribute("Mass",getMass()));
	attr.push_back(Attribute("Thrust Power",thrust));
	attr.push_back(Attribute("Usage Drain",usageDrain));
	attr.push_back(Attribute("Usage Heat",usageHeat));
	attr.push_back(Attribute("Overheat Threshold",heatCapacity));
	attr.push_back(Attribute("Cooling Rate",coolingRate));
	return attr;
}

double Thruster::getThrust() {
	return thrust;
}

void Thruster::setThrust(double thrust) {
	this->thrust = thrust;
}

double Thruster::getUsageDrain() {
	return usageDrain;
}

void Thruster::setUsageDrain(double usageDrain) {
	this->usageDrain = usageDrain;
}

double Thruster::getUsageHeat() {
	return usageHeat;
}

void Thruster::setUsageHeat(double usageHeat) {
	this->usageHeat = usageHeat;
}

double Thruster::getHeatCapacity() {
	return heatCapacity;
}

void Thruster::setHeatCapacity(double heatCapacity) {
	this->heatCapacity = heatCapacity;
}

double Thruster::getCoolingRate() {
	return coolingRate;
}

void Thruster::setCoolingRate(double coolingRate) {
	this->coolingRate = coolingRate;
}