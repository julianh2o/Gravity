/*
 *  EquipmentCollection.cpp
 *  Gravity
 *
 *  Created by Julian on 8/25/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "EquipmentCollection.h"

EquipmentCollection::EquipmentCollection() {
	for (int i=0; i<NUM_PART_TYPES; i++) {
		parts.push_back(NULL);
	}
}

EquipmentCollection::~EquipmentCollection() {
	
}

void EquipmentCollection::setPartSet(PartType type, PartSet * partset) {
	parts[type] = partset;
}

int EquipmentCollection::getPartCount(PartType type) {
	return parts[type]->getSize();
}

int EquipmentCollection::getTypeCount() {
	return NUM_PART_TYPES;
}

Part* EquipmentCollection::getPart(PartType type, int partId) {
	return parts[type]->getPartAt(partId);
}