/*
 *  Radiator.cpp
 *  Gravity
 *
 *  Created by Julian on 8/22/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Radiator.h"

Radiator::Radiator(double systemCoolingRate, double singleCoolingRate, double emergencyRate, double energyDrain, double flashCoolingRate, double flashCoolingCapacity, double flashCoolingRecharge, double mass) : Part(mass) {
	this->systemCoolingRate = systemCoolingRate;
	this->singleCoolingRate = singleCoolingRate;
	this->emergencyRate = emergencyRate;
	this->energyDrain = energyDrain;
	this->flashCoolingRate = flashCoolingRate;
	this->flashCoolingCapacity = flashCoolingCapacity;
	this->flashCoolingRecharge = flashCoolingRecharge;
}

void Radiator::a() {
	
}

std::vector<Attribute> Radiator::getAttributes() {
	std::vector<Attribute> attr = std::vector<Attribute>();
	attr.push_back(Attribute("Mass",getMass()));
	attr.push_back(Attribute("System Cooling Rate",systemCoolingRate));
	attr.push_back(Attribute("Single Cooling Rate",singleCoolingRate));
	attr.push_back(Attribute("Emergency Cooling Rate",emergencyRate));
	attr.push_back(Attribute("Energy Drain",energyDrain));
	attr.push_back(Attribute("Flash Cooling Rate",flashCoolingRate));
	attr.push_back(Attribute("Flash Cooling Capacity",flashCoolingCapacity));
	attr.push_back(Attribute("Flash Cooling Recharge",flashCoolingRecharge));
	return attr;
}
	

double Radiator::getSystemCoolingRate() {
	return systemCoolingRate;
}

void Radiator::setSystemCoolingRate(double systemCoolingRate) {
	this->systemCoolingRate = systemCoolingRate;
}

double Radiator::getSingleCoolingRate() {
	return singleCoolingRate;
}

void Radiator::setSingleCoolingRate(double singleCoolingRate) {
	this->singleCoolingRate = singleCoolingRate;
}

double Radiator::getEmergencyRate() {
	return emergencyRate;
}

void Radiator::setEmergencyRate(double emergencyRate) {
	this->emergencyRate = emergencyRate;
}

double Radiator::getEnergyDrain() {
	return energyDrain;
}

void Radiator::setEnergyDrain(double energyDrain) {
	this->energyDrain = energyDrain;
}

double Radiator::getFlashCoolingRate() {
	return flashCoolingRate;
}

void Radiator::setFlashCoolingRate(double flashCoolingRate) {
	this->flashCoolingRate = flashCoolingRate;
}

double Radiator::getFlashCoolingCapacity() {
	return flashCoolingCapacity;
}

void Radiator::setFlashCoolingCapacity(double flashCoolingCapacity) {
	this->flashCoolingCapacity = flashCoolingCapacity;
}

double Radiator::getFlashCoolingRecharge() {
	return flashCoolingRecharge;
}

void Radiator::setFlashCoolingRecharge(double flashCoolingRecharge) {
	this->flashCoolingRecharge = flashCoolingRecharge;
}