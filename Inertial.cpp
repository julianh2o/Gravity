/*
 *  Inertial.cpp
 *  Gravity
 *
 *  Created by Julian on 8/18/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Inertial.h"

Inertial::Inertial() : Vector2D() {
	mass = 1;
}

Inertial::Inertial(double x, double y, double xvel, double yvel, double mass) : Vector2D(x,y) {
	vel = Vector2D(xvel,yvel);
	this->mass = mass;
}

Inertial::Inertial(const Vector2D &pos, const Vector2D &vel, double mass) : Vector2D(pos.getX(),pos.getY()) {
	this->vel = Vector2D(vel);
	this->mass = mass;
}

void Inertial::updatePos(int delta) {
	*this += vel.timeConvert(delta);
}

double Inertial::distanceTo(Inertial * a) const {
	Vector2D diff = *this - *a;
	return diff.getMagnitude();
}

const Vector2D Inertial::getVel() const {
	return vel;
}

void Inertial::setVel(double x, double y) {
	vel.set(x,y);
}

void Inertial::setVel(const Vector2D &a) {
	vel.set(a.getX(),a.getY());
}

void Inertial::incVel(double x, double y) {
	vel.incX(x);
	vel.incY(y);
}

void Inertial::incVel(const Vector2D &a) {
	vel += a;
}

double Inertial::getMass() {
	return mass;
}

void Inertial::setMass(double mass) {
	this->mass = mass;
}