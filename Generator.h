/*
 *  Generator.h
 *  Gravity
 *
 *  Created by Julian on 8/22/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Generator_H
#define Generator_H

#include "Part.h"

class Generator : public Part {
private:
	double energyOutput;
	double emergencyOutput;
	double usageHeat;
	double heatCapacity;
	double coolingRate;

public:
	Generator(double energyOutput, double emergencyOutput, double usageHeat, double heatCapacity, double coolingRate, double mass);

	void a();
	std::vector<Attribute> getAttributes();

	double getEnergyOutput();
	void setEnergyOutput(double energyOutput);
	double getEmergencyOutput();
	void setEmergencyOutput(double emergencyOutput);
	double getUsageHeat();
	void setUsageHeat(double usageHeat);
	double getHeatCapacity();
	void setHeatCapacity(double heatCapacity);
	double getCoolingRate();
	void setCoolingRate(double coolingRate);
};

#endif