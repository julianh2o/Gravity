/*
 *  PartSet.h
 *  Gravity
 *
 *  Created by Julian on 8/26/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef PartSet_H
#define PartSet_H

#include <vector>
#include "Part.h"

class PartSet {
	std::vector<Part*> parts;
public:
	PartSet();
	void addPart(Part * part);
	int getSize();
	Part * getPartAt(int index);
};

#endif