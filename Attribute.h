/*
 *  Attribute.h
 *  Gravity
 *
 *  Created by Julian on 8/23/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Attribute_H
#define Attribute_H

#include <string>

class Attribute {
private:
	std::string name;
	double value;
	
public:
	Attribute(std::string name, double value);
	std::string Attribute::getString();
	std::string getName();
	void setName(std::string name);
	double getValue();
	void setValue(double value);
};

#endif