/*
 *  View.cpp
 *  Gravity
 *
 *  Created by Julian on 8/19/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "View.h"

View::View() {
	set(0,0);
	current = target = 1;
}

View::View(double x, double y) {
	set(x,y);
	current = target = 1;
}

void View::setMouse(int x, int y) {
	mouse = Vector2D(x,y);
}

Vector2D View::getMouse() {
	Vector2D foo = mouse*(1/current);
	return mouse*(1/current) + *this - size/(2*current);
}

void View::zoomIn() {
	if (target<2) target *= 2;
}
void View::zoomOut() {
	if (target>.5) target /= 2;
}

void View::update(int delta) {
	double adjust = 5;
	if (target != current) {
		if (fabs(target-current) < pps(adjust,delta)) {
			current = target;
		} else {
			if (target > current) {
				current += pps(adjust,delta);
			} else {
				current -= pps(adjust,delta);
			}
		}
	}
	GLint vPort[4];
	glGetIntegerv(GL_VIEWPORT, vPort);
	size.set(vPort[2],vPort[3]);
}

void View::applyGUI() {
	glOrtho(0, size.getX(), size.getY(), 0, -1, 1);
}

void View::apply() {
	double scale = 1/current;
	glOrtho(0, size.getX()*scale, size.getY()*scale, 0, -1, 1);
	int x = -getX() + size.getX()*scale/2;
	int y = -getY() + size.getY()*scale/2;
	glTranslatef(x, y, 0.0);
}