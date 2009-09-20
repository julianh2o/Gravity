/*
 *  PartSet.cpp
 *  Gravity
 *
 *  Created by Julian on 8/26/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "PartSet.h"

PartSet::PartSet() {
	
}

void PartSet::addPart(Part * part) {
	parts.push_back(part);
}

int PartSet::getSize() {
	return parts.size();
}

Part * PartSet::getPartAt(int index) {
	return parts[index];
}