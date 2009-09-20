/*
 *  Color.h
 *  Gravity
 *
 *  Created by Julian on 8/22/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#ifndef Color_H
#define Color_H

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif

class Color {
	int red;
	int green;
	int blue;
public:
	Color(int red, int green, int blue);
	void set();
	
	int bound(int a, int min, int max);
	
	int getRed();
	void setRed(int red);
	int getGreen();
	void setGreen(int green);
	int getBlue();
	void setBlue(int blue);
};

#endif;