/*
 *  Color.cpp
 *  Gravity
 *
 *  Created by Julian on 8/22/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Color.h"

Color::Color(int red, int green, int blue) {
	setRed(red);
	setGreen(green);
	setBlue(blue);
}

int Color::bound(int a, int min, int max) {
	if (a < min) a = min;
	if (a > max) a = max;
	return a;
}

void Color::set() {
	glColor3f(red/255.0,green/255.0,blue/255.0);
}

int Color::getRed() {
	return red;
}

void Color::setRed(int red) {
	this->red = bound(red,0,255);
}

int Color::getGreen() {
	return green;
}

void Color::setGreen(int green) {
	this->green = bound(green,0,255);
}

int Color::getBlue() {
	return blue;
}

void Color::setBlue(int blue) {
	this->blue = bound(blue,0,255);
}