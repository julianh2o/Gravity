/*
 *  Radiator.h
 *  Gravity
 *
 *  Created by Julian on 8/22/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Radiator_H
#define Radiator_H

#include "Part.h"

class Radiator : public Part {
private:
	double systemCoolingRate;
	double singleCoolingRate;
	double emergencyRate;
	double energyDrain;
	double flashCoolingRate;
	double flashCoolingCapacity;
	double flashCoolingRecharge;
	
public:
	Radiator(double systemCoolingRate, double singleCoolingRate, double emergencyRate, double energyDrain, double flashCoolingRate, double flashCoolingCapacity, double flashCoolingRecharge, double mass);

	void a();
	std::vector<Attribute> getAttributes();

	double getSystemCoolingRate();
	void setSystemCoolingRate(double systemCoolingRate);
	double getSingleCoolingRate();
	void setSingleCoolingRate(double singleCoolingRate);
	double getEmergencyRate();
	void setEmergencyRate(double emergencyRate);
	double getEnergyDrain();
	void setEnergyDrain(double energyDrain);
	double getFlashCoolingRate();
	void setFlashCoolingRate(double flashCoolingRate);
	double getFlashCoolingCapacity();
	void setFlashCoolingCapacity(double flashCoolingCapacity);
	double getFlashCoolingRecharge();
	void setFlashCoolingRecharge(double flashCoolingRecharge);
};

#endif