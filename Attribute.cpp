/*
 *  Attribute.cpp
 *  Gravity
 *
 *  Created by Julian on 8/23/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Attribute.h"

Attribute::Attribute(std::string name, double value) {
	this->name = name;
	this->value = value;
}

std::string Attribute::getString() {
	char buf[getName().size() + 10];
	sprintf(buf,"%s: %.2f\n",getName().c_str(),getValue());
	return std::string(buf);
}

std::string Attribute::getName() {
	return name;
}

void Attribute::setName(std::string name) {
	this->name = name;
}

double Attribute::getValue() {
	return value;
}

void Attribute::setValue(double value) {
	this->value = value;
}