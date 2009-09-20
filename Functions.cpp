/*
 *  Functions.cpp
 *  SDLOGL
 *
 *  Created by Julian on 6/28/09.
 *  Copyright 2009 Julian Hartline. All rights reserved.
 *
 */

#include "Functions.h"

double dist(double x, double y, double xx, double yy) {
	return sqrt((xx-x)*(xx-x) + (yy-y)*(yy-y));
}

double pps(double pixels, int time) {
	return pixels*time/1000;
}

double angleTo(double a1, double a2) {
	double angle = a1 - a2;
	while (fabs(angle) > M_PI) {
		if (angle > 0) {
			angle -= M_PI*2;
		} else {
			angle += M_PI*2;
		}
	}
	return angle;
}

int bound(int a, int min, int max) {
	if (a < min) a = min;
	if (a > max) a = max;
	return a;
}

double bound(double a, double min, double max) {
	if (a < min) a = min;
	if (a > max) a = max;
	return a;	
}

//returns the absolute path to the app bundle's resource folder.
char* getResourcePath() {
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
	char *path = (char*)malloc(PATH_MAX);
	CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX);
	CFRelease(resourcesURL);
	return path;
}

char* createPath(const char* s) {
	return strcat(getResourcePath(),s);
}

std::vector<std::string>* readFile(std::string filename) {
	using namespace std;
	
	vector<string>* vec = new vector<string>;
	
	char *rsc = getResourcePath();
	chdir(rsc);

	string rscs(rsc);
	free(rsc);
	rscs+="/"+filename;
	
	fstream file;
	file.open(rscs.c_str(),ios::in);
	if (file.fail()) {
		printf("FAILED\n");
		return vec;
	}
	string line;
	while(!file.eof()) {
		getline(file,line);
		vec->push_back(line);
	}
	file.close();
	return vec;
}

std::vector<std::string>* splitString(std::string str, char delim) {
	using namespace std;
	
	vector<string>* vec = new vector<string>;
	int pos = 0;
	int lpos = -1;
	while(pos!=string::npos) {
		pos = str.find_first_of(delim,pos+1);
		string s = str.substr(lpos+1,pos-lpos-1);
		vec->push_back(s);
		lpos = pos;
	}
	return vec;
}

void makeBar(double x, double y, double barwidth, double barheight, double val, double max, bool horz, Color background, Color foreground) {
	background.set();
	glBegin(GL_POLYGON);
	rect(x,y,x+barwidth,y+barheight);
	glEnd();
	glBegin(GL_POLYGON);
	foreground.set();
	if (val < 0) val = 0;
	if (val > max) val = max;
	double full = (val/max);
	double empty = 1-full;
	if (horz) {
		rect(x,y,x+barwidth*full,y+barheight);
	} else {
		rect(x,y+barheight*empty,x+barwidth,y+barheight);
	}
	glEnd();
}

void gvi(double x, double y) {
	glVertex2f(x+.325,y+.325);
}

void gvi(const Vector2D &a) {
	gvi(a.getX(),a.getY());
}

void dot(double x, double y, double size) {
	gvi(x-size/2,y-size/2);
	gvi(x+size/2,y-size/2);
	gvi(x+size/2,y+size/2);
	gvi(x-size/2,y+size/2);
}

void dot(Vector2D &a, double size) {
	dot(a.getX(),a.getY(),size);
}

void rect(double x1, double y1, double x2, double y2) {
	glTexCoord2f(0.,0.);
	gvi(x1,y1);

	float xcalc = (x2-x1)/64.;
	float ycalc = (y2-y1)/64.;
	glTexCoord2f(xcalc,0.);
	gvi(x2,y1);

	glTexCoord2f(xcalc,ycalc);
	gvi(x2,y2);

	glTexCoord2f(0.,ycalc);
	gvi(x1,y2);
}

void circle(double x, double y, double radius) {
	int px,py;
	int segments = 100;
	for (double c=0; c<M_PI*2; c += (M_PI*2/segments)) {
		double xx = x + radius*cos(c);
		double yy = y + radius*sin(c);
		if (c != 0) {
			gvi(xx,yy);
			gvi(px,py);
		}
		px = xx;
		py = yy;
	}	
}

void drawText(double x, double y, std::string s, void* font) {
	glRasterPos2f(x,y);
	for (int i = 0; i < s.size(); i++) {
		glutBitmapCharacter(font, s.c_str()[i]);
	}
}

int stringWidth(std::string s, void* font) {
	int c = 0;
	for (int i = 0; i < s.size(); i++) {
		c += glutBitmapWidth(font,s.c_str()[i]);
	}
	return c;
}

std::vector<std::string>* getLevelList() {
	using namespace std;
	char *rsc = getResourcePath();
	
	string rscs(rsc);
	rscs+="/Levels/";
	rscs = "ls -1 "+rscs;
	FILE *fp = popen(rscs.c_str(),"r");
	char buff[100];
	string s;
	while (fgets(buff, sizeof(buff), fp) != NULL) {
		s+=buff;
	}
	vector<string> *spl = splitString(s,'\n');
	if ((*spl)[spl->size()-1]=="") {
		spl->pop_back();
	}
	for (vector<string>::iterator it = spl->begin(); it < spl->end(); it++) {
		string *str = &(*it);
		int ind = str->find(".data");
		if (ind != string::npos) {
			str = new string(str->substr(0,ind));
			*it = *str;
		} else {
			spl->erase(it);
			it--;
		}
	}
	return spl;
}

int loadTextureBMP(const char *path) {
	SDL_Surface *image;
	GLuint texture;
	GLenum format;
	image = SDL_LoadBMP(createPath(path));
	if (image==NULL) {
		printf("Failed to load texture: %s\n",path);
		exit(1);
	} else {
		printf("Surface: w:%d h:%d bpp:%d\n", image->w, image->h, image->format->BitsPerPixel);
		int colorBytes = image->format->BytesPerPixel;
		if (image->format->Rmask == 0x000000ff) {
			if (colorBytes == 3) {
				format = GL_RGB;
			} else if (colorBytes == 4) {
				format = GL_BGR;
			}
		} else {
			if (colorBytes == 3) {
				format = GL_RGBA;
			} else if (colorBytes == 4) {
				format = GL_BGRA;
			} 	
		}
		printf("bytes per pixel: %d\n",colorBytes);
		glGenTextures(1,&texture);
		glBindTexture(GL_TEXTURE_2D,texture);
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		
		glTexImage2D( GL_TEXTURE_2D, 0, colorBytes, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels );
		SDL_FreeSurface(image);
		return texture;
	}
}