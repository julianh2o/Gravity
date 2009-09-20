/*
 *  Functions.h
 *  Gravity
 *
 *  Created by Julian on 6/28/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Functions_H
#define Functions_H

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "math.h"

#include "CoreFoundation/CoreFoundation.h"

#include "Vector2D.h"
#include "Color.h"

double dist(double x, double y, double xx, double yy);
double pps(double pixels, int time);

double angleTo(double a1, double a2);

int bound(int a, int min, int max);
double bound(double a, double min, double max);

char* getResourcePath();
char* createPath(const char* s);

std::vector<std::string>* readFile(std::string filename);
std::vector<std::string>* splitString(std::string str, char delim);

void makeBar(double x, double y, double width, double height, double val, double max, bool horz, Color background, Color foreground);

void gvi(double x, double y);
void gvi(const Vector2D &a);

void dot(double x, double y, double size);
void dot(Vector2D &a, double size);

void rect(double x1, double y1, double x2, double y2);
void circle(double x, double y, double radius);
void drawText(double x, double y, std::string s, void* font);
int stringWidth(std::string s, void* font);

std::vector<std::string>* getLevelList();
int loadTextureBMP(const char *path);

#endif