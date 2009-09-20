/*
 *  Vector2D.cpp
 *  Gravity
 *
 *  Created by Julian on 8/17/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Vector2D.h"

Vector2D::Vector2D() {
	set(0,0);
}

Vector2D::Vector2D(double x, double y) {
	set(x,y);
}

Vector2D::Vector2D(double angle) {
	set(cos(angle),sin(angle));
}

double Vector2D::getMagnitude() const {
	return sqrt(x*x+y*y);
}

double Vector2D::getAngle() const {
	return M_PI/2-atan2(x,y);
}

Vector2D Vector2D::getUnitVector() const {
	double mag = getMagnitude();
	return Vector2D(x/mag,y/mag);
}

const Vector2D Vector2D::timeConvert(int delta) const {
	return Vector2D(*this)*(delta/1000.0);
}

Vector2D& Vector2D::operator=(const Vector2D &a) {
	if (this != &a) {
		set(a.x, a.y);
	}
	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D &a) {
	incX(a.x);
	incY(a.y);
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D &a) {
	incX(-a.x);
	incY(-a.y);
	return *this;
}

Vector2D& Vector2D::operator*=(const double a) {
	setX(x*a);
	setY(y*a);
	return *this;
}

Vector2D& Vector2D::operator/=(const double a) {
	setX(x/a);
	setY(y/a);
	return *this;
}

const Vector2D Vector2D::operator+(const Vector2D &a) const {
	return Vector2D(*this) += a;
}

const Vector2D Vector2D::operator-(const Vector2D &a) const {
	return Vector2D(*this) -= a;
}

const Vector2D Vector2D::operator*(const double a) const {
	return Vector2D(*this) *= a;
}

const Vector2D Vector2D::operator/(const double a) const {
	return Vector2D(*this) /= a;
}

void Vector2D::set(double x, double y) {
	setX(x);
	setY(y);
}

double Vector2D::getX() const {
	return x;
}

void Vector2D::setX(double x) {
	this->x = x;
}

void Vector2D::incX(double xx) {
	setX(getX()+xx);
}

double Vector2D::getY() const {
	return y;
}

void Vector2D::setY(double y) {
	this->y = y;
}

void Vector2D::incY(double yy) {
	setY(getY()+yy);
}