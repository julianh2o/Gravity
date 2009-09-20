/*
 *  Vector2D.h
 *  Gravity
 *
 *  Created by Julian on 8/17/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Vector2D_H
#define Vector2D_H

#include "math.h"

class Vector2D {
	double x;
	double y;
public:
	Vector2D();
	Vector2D(double x, double y);
	Vector2D(double angle);

	double getMagnitude() const;
	double getAngle() const;
	Vector2D getUnitVector() const;
	const Vector2D timeConvert(int delta) const;
	
	Vector2D& operator=(const Vector2D &a);

	Vector2D& operator+=(const Vector2D &a);
	Vector2D& operator-=(const Vector2D &a);
	Vector2D& operator*=(const double a);
	Vector2D& operator/=(const double a);

	const Vector2D operator+(const Vector2D &a) const;
	const Vector2D operator-(const Vector2D &a) const;
	const Vector2D operator*(const double a) const;
	const Vector2D operator/(const double a) const;

	void set(double x, double y);
	double getX() const;
	void setX(double x);
	void incX(double xx);
	double getY() const;
	void setY(double y);
	void incY(double yy);
};


#endif