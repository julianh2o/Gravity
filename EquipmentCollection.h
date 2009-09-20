/*
 *  EquipmentCollection.h
 *  Gravity
 *
 *  Created by Julian on 8/25/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef EquipmentCollection_H
#define EquipmentCollection_H

#include <vector>

#include "Part.h"
#include "PartSet.h"

class EquipmentCollection {
	static const int NUM_PART_TYPES = 4;
	std::vector<PartSet*> parts;
//	std::string PartNames [] = {"Radiator", "Generator", "Capacitor", "Thruster"};
public:
	enum PartType { RADIATOR, GENERATOR, CAPACITOR, THRUSTER };
	EquipmentCollection();
	~EquipmentCollection();
	void setPartSet(PartType type, PartSet * partset);
	int getPartCount(PartType type);
	int getTypeCount();
	Part* getPart(PartType type, int partId);
};

#endif