/*
 *  Part.h
 *  Gravity
 *
 *  Created by Julian on 8/21/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Part_H
#define Part_H

#include <string>
#include <vector>

#include "Attribute.h"

class Part {
private:
	double mass;
public:
	Part();
	Part(double mass);

	virtual void a() {}; //filler
	virtual std::vector<Attribute> getAttributes() {
		return std::vector<Attribute>();
	}
	
	double getMass();
	void setMass(double mass);
};

#endif