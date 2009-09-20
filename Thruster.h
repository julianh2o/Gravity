/*
 *  Thruster.h
 *  Gravity
 *
 *  Created by Julian on 8/21/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Thruster_H
#define Thruster_H

#include "Part.h"

class Thruster : public Part {
private:
	double thrust;
	double usageDrain;
	double usageHeat;
	double heatCapacity;
	double coolingRate;

public:
	Thruster(double thrust, double usageDrain, double usageHeat, double heatCapacity, double coolingRate, double mass);
	
	void a();
	std::vector<Attribute> getAttributes();

	double getThrust();
	void setThrust(double thrust);
	double getUsageDrain();
	void setUsageDrain(double usageDrain);
	double getUsageHeat();
	void setUsageHeat(double usageHeat);
	double getHeatCapacity();
	void setHeatCapacity(double heatCapacity);
	double getCoolingRate();
	void setCoolingRate(double coolingRate);	
};

#endif