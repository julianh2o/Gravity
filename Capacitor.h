/*
 *  Capacitor.h
 *  Gravity
 *
 *  Created by Julian on 8/21/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Capacitor_H
#define Capacitor_H

#include "Part.h"

class Capacitor : public Part {
private:
	double capacity;
	double overchargeLeak;
	
public:
	Capacitor(double capacity, double overchargeLeak, double mass);
	
	void a();
	std::vector<Attribute> getAttributes();
	
	double getCapacity();
	void setCapacity(double capacity);
	double getOverchargeLeak();
	void setOverchargeLeak(double overchargeLeak);
};

#endif