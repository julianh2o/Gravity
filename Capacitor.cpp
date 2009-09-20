/*
 *  Capacitor.cpp
 *  Gravity
 *
 *  Created by Julian on 8/21/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Capacitor.h"

Capacitor::	Capacitor(double capacity, double overchargeLeak, double mass) : Part(mass) { 
	this->capacity = capacity;
	this->overchargeLeak = overchargeLeak;
}

void Capacitor::a() {
	
}

std::vector<Attribute> Capacitor::getAttributes() {
	std::vector<Attribute> attr = std::vector<Attribute>();
	attr.push_back(Attribute("Mass",getMass()));
	attr.push_back(Attribute("Capacity",capacity));
	attr.push_back(Attribute("Overcharge Leak",overchargeLeak));
	return attr;
}

double Capacitor::getCapacity() {
	return capacity;
}

void Capacitor::setCapacity(double capacity) {
	this->capacity = capacity;
}

double Capacitor::getOverchargeLeak() {
	return overchargeLeak;
}

void Capacitor::setOverchargeLeak(double overchargeLeak) {
	this->overchargeLeak = overchargeLeak;
}