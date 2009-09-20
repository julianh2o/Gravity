/*
 *  Projectile.cpp
 *  Gravity
 *
 *  Created by Julian on 8/20/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Projectile.h"

Projectile::Projectile() : Inertial() {
	life = 2000;
}

Projectile::Projectile(const Vector2D &pos, const Vector2D &vel) : Inertial(pos,vel,1) {
	life = 2000;
}

void Projectile::update(int delta) {
	if (tail.size() > 10) tail.erase(tail.begin());
	tail.push_back(Vector2D(getX(), getY()));
	life -= delta;
	updatePos(delta);
}

void Projectile::draw() {
	glColor3f(1.0,0.0,0.0);
//	glBegin(GL_LINES);
//	Vector2D pos = Vector2D(getX(),getY());
//	Vector2D tip = pos + Vector2D(getHeading())*10;
//	gvi(pos);
//	gvi(tip);
//	glEnd();
	
//	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	dot(getX(), getY(), 3);
	glEnd();

	glBegin(GL_LINES);
	for (int i=1; i < tail.size(); i++) {
		gvi(tail[i-1].getX(),tail[i-1].getY());
		gvi(tail[i].getX(),tail[i].getY());
	}
	glEnd();
}

void Projectile::kill() {
	setLife(0);
}

bool Projectile::isDead() {
	if (life <= 0) return true;
	return false;
}

int Projectile::getLife() {
	return life;
}

void Projectile::setLife(int life) {
	this->life = life;
}

void Projectile::thrust(double force) {
	Vector2D dir = Vector2D(heading);
	dir *= force;
	incVel(dir);
}

void Projectile::setHeading(double heading) {
	this->heading = heading;
}

double Projectile::getHeading() {
	return heading;
}

void Projectile::incHeading(double heading) {
	this->heading += heading;
}