/*
 *  EquipMenu.cpp
 *  Gravity
 *
 *  Created by Julian on 8/24/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "EquipMenu.h"

int centerx = 400;
int centery = 400;
int width = 160;
int spacingx = 2;
int height = 160;
int spacingy = 20;

EquipMenu::EquipMenu(EquipmentCollection * eq, Ship * ship) {
	this->eq = eq;
	this->ship = ship;
	targetX = std::vector<int>();
	offsetX = std::vector<double>();
	for (int y=0; y<eq->getTypeCount(); y++) {
		for (int x=0; x<eq->getPartCount((EquipmentCollection::PartType)y); x++) {
			if (eq->getPart((EquipmentCollection::PartType)y,x) == ship->getPart((EquipmentCollection::PartType)y)) {
				targetX.push_back(x);
				break;
			}
		}
		offsetX.push_back(0);
	}
	targetY = 0;
	offsetY = 0;
	update(3000);
}

void EquipMenu::draw() {
	for (int y=0; y<eq->getTypeCount(); y++) {
		for (int x=0; x<eq->getPartCount((EquipmentCollection::PartType)y); x++) {
			int topleftX = - offsetX[y] + centerx - width/2 + (width + spacingx)*(x);
			int topleftY = - offsetY + centery - height/2 + (height + spacingy)*(y);
			double mag = dist(centerx, centery, topleftX+width/2, topleftY+height/2);
			if (mag < 255) {
				int c = (255-mag);
				Color(c,c,c).set();
				if (eq->getPart((EquipmentCollection::PartType)y,x) == ship->getPart((EquipmentCollection::PartType)y)) {
					Color(c/2,c/2,c).set();					
				}
				glBegin(GL_LINE_LOOP);
				rect(topleftX,topleftY,topleftX+width,topleftY+height);
				glEnd();
				Color(c,c,c).set();
				std::vector<Attribute> attribs = eq->getPart((EquipmentCollection::PartType)y,x)->getAttributes();
				for (int i=0; i<attribs.size(); i++) {
					drawText(topleftX+5,topleftY+14+20*i,attribs[i].getString(),GLUT_BITMAP_HELVETICA_10);
				}
			}
		}
	}
}

void EquipMenu::update(int delta) {
	double speed = 700;
	for (int i=0; i<eq->getTypeCount(); i++) {
		int targetOffsetX = targetX[i]*(width + spacingx);
		if (offsetX[i] < targetOffsetX) {
			offsetX[i] += pps(speed,delta);
			if (offsetX[i] > targetOffsetX) offsetX[i] = targetOffsetX;
		} else {
			offsetX[i] -= pps(speed,delta);
			if (offsetX[i] < targetOffsetX) offsetX[i] = targetOffsetX;		
		}
	}
	int targetOffsetY = targetY*(height + spacingy);
	if (offsetY < targetOffsetY) {
		offsetY += pps(speed,delta);
		if (offsetY > targetOffsetY) offsetY = targetOffsetY;
	} else {
		offsetY -= pps(speed,delta);
		if (offsetY < targetOffsetY) offsetY = targetOffsetY;
	}
}

void EquipMenu::left() {
	targetX[targetY]--;
	if (targetX[targetY] < 0) targetX[targetY] = 0;
	ship->equip(eq->getPart((EquipmentCollection::PartType)targetY,targetX[targetY]));
}

void EquipMenu::right() {
	int partcount = eq->getPartCount((EquipmentCollection::PartType)targetY);
	targetX[targetY]++;

	if (targetX[targetY] > partcount-1) targetX[targetY] = partcount-1;
	ship->equip(eq->getPart((EquipmentCollection::PartType)targetY,targetX[targetY]));
}

void EquipMenu::up() {
	targetY--;
	if (targetY < 0) targetY = 0;
}

void EquipMenu::down() {
	targetY++;
	if (targetY > eq->getTypeCount()-1) targetY = eq->getTypeCount()-1;
}