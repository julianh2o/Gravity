/*
 *  Planet.cpp
 *  Gravity
 *
 *  Created by Julian on 8/18/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Planet.h"

Planet::Planet() {
	pos = Vector2D(0,0);
	mass = 1;
	radius = 50;
}

Planet::Planet(double x, double y, double mass, double radius) {
	pos = Vector2D(x,y);
	this->mass = mass;
	this->radius = radius;
}

void Planet::update(int delta) {
	
}

void Planet::draw() {
	glColor3f(1.,1.,1.);
	glBegin(GL_LINE_LOOP);
	circle(pos.getX(),pos.getY(),radius);
	glEnd();
}

void Planet::affect(Inertial * a, int delta) {
	Vector2D diff = *a - pos;
	double mag = diff.getMagnitude();
	Vector2D unitv = diff.getUnitVector();
	double mu = (a->getMass() * getMass() * GRAV_G);
	unitv *= -pps(mu/(mag*mag),delta);
	a->incVel(unitv);
}

double Planet::distanceTo(Inertial * a) {
	Vector2D diff = *a - pos;
	return diff.getMagnitude();
}

const Vector2D Planet::getPos() {
	return pos;
}

double Planet::getX() {
	return pos.getX();
}

void Planet::setX(double x) {
	pos.setX(x);
}

double Planet::getY() {
	return pos.getY();
}

void Planet::setY(double y) {
	pos.setY(y);
}

double Planet::getMass() {
	return mass;
}

void Planet::setMass(double mass) {
	this->mass = mass;
}

double Planet::getRadius() {
	return radius;
}

void Planet::setRadius(double radius) {
	this->radius = radius;
}
