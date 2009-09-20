/*
 *  Inertial.h
 *  Gravity
 *
 *  Created by Julian on 8/18/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Inertial_H
#define Inertial_H

#include "Vector2D.h"

class Inertial : public Vector2D {
	Vector2D vel;
	double mass;
public:
	Inertial();
	Inertial(double x, double y, double xvel, double yvel, double mass);
	Inertial(const Vector2D &pos, const Vector2D &vel, double mass);
	
	void updatePos(int delta);
	
	double distanceTo(Inertial * a) const;
	
	const Vector2D getVel() const;
	void setVel(double x, double y);
	void setVel(const Vector2D &a);
	void incVel(double x, double y);
	void incVel(const Vector2D &a);
	
	double getMass();
	void setMass(double mass);
};

#endif