/*
 *  Generator.cpp
 *  Gravity
 *
 *  Created by Julian on 8/22/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Generator.h"

Generator::Generator(double energyOutput, double emergencyOutput, double usageHeat, double heatCapacity, double coolingRate, double mass) : Part(mass) {
	this->energyOutput = energyOutput;
	this->emergencyOutput = emergencyOutput;
	this->usageHeat = usageHeat;
	this->heatCapacity = heatCapacity;
	this->coolingRate = coolingRate;
}

void Generator::a() {
	
}

std::vector<Attribute> Generator::getAttributes() {
	std::vector<Attribute> attr = std::vector<Attribute>();
	attr.push_back(Attribute("Mass",getMass()));
	attr.push_back(Attribute("Energy Output",energyOutput));
	attr.push_back(Attribute("Emergency Output",emergencyOutput));
	attr.push_back(Attribute("Usage Heat",usageHeat));
	attr.push_back(Attribute("Overheat Threshold",heatCapacity));
	attr.push_back(Attribute("Cooling Rate",coolingRate));
	return attr;
}

double Generator::getEnergyOutput() {
	return energyOutput;
}

void Generator::setEnergyOutput(double energyOutput) {
	this->energyOutput = energyOutput;
}

double Generator::getEmergencyOutput() {
	return emergencyOutput;
}

void Generator::setEmergencyOutput(double emergencyOutput) {
	this->emergencyOutput = emergencyOutput;
}

double Generator::getUsageHeat() {
	return usageHeat;
}

void Generator::setUsageHeat(double usageHeat) {
	this->usageHeat = usageHeat;
}

double Generator::getHeatCapacity() {
	return heatCapacity;
}

void Generator::setHeatCapacity(double heatCapacity) {
	this->heatCapacity = heatCapacity;
}

double Generator::getCoolingRate() {
	return coolingRate;
}

void Generator::setCoolingRate(double coolingRate) {
	this->coolingRate = coolingRate;
}