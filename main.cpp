#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "SDL.h"

#ifdef __WIN32__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>
#endif

#include "Gravity.h"

static SDL_Surface *gScreen;
static Gravity gravity;

static void initAttributes () {
    // Setup attributes we want for the OpenGL context
    
    int value;

    value = 16;
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, value);

    value = 1;
    SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, value);
}

static void printAttributes () {
    // Print out attributes of the context we created
    int nAttr;
    int i;
    
    SDL_GLattr attr[] = { SDL_GL_RED_SIZE, SDL_GL_BLUE_SIZE, SDL_GL_GREEN_SIZE,
                    SDL_GL_ALPHA_SIZE, SDL_GL_BUFFER_SIZE, SDL_GL_DEPTH_SIZE };
                    
    char *desc[] = { "Red size: %d bits\n", "Blue size: %d bits\n", "Green size: %d bits\n",
                     "Alpha size: %d bits\n", "Color buffer size: %d bits\n", 
                     "Depth bufer size: %d bits\n" };

    nAttr = sizeof(attr) / sizeof(int);
    
    for (i = 0; i < nAttr; i++) {
    
        int value;
        SDL_GL_GetAttribute (attr[i], &value);
        printf (desc[i], value);
    } 
}

static void createSurface (int fullscreen) {
    Uint32 flags = 0;
    fullscreen = 0;
    flags = SDL_OPENGL;
    if (fullscreen)
        flags |= SDL_FULLSCREEN;
    
    // Create window
	
	//640, 480
	//1024, 640
	const SDL_VideoInfo * vi = SDL_GetVideoInfo();
	 
	int resx = vi->current_w;
	int resy = vi->current_h;
	resx = 1024;
	resy = 640;
    gScreen = SDL_SetVideoMode(resx, resy, 0, flags);
    if (gScreen == NULL) {
		
        fprintf (stderr, "Couldn't set 640x480 OpenGL video mode: %s\n",
                 SDL_GetError());
		SDL_Quit();
		exit(2);
	}
}

static void glEnable2D() {

	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glTranslatef (0.375, 0.375, 0.);
	glPushMatrix();
	glLoadIdentity();
}

static void initGL() {
	glEnable2D();
}

static void drawGL() {
	glClear(GL_COLOR_BUFFER_BIT);
	gravity.draw();
}

static void mainLoop () {
    SDL_Event event;
    int done = 0;
    int lastTicks = -1;
    int nowTicks;
	int delta = 0;
    
    while ( !done ) {
		
        if (lastTicks > 0) {
            nowTicks = SDL_GetTicks();
			delta = nowTicks-lastTicks;
            lastTicks = nowTicks;
        } else {
            lastTicks = SDL_GetTicks();
        }

		/* Check for events */
		while ( SDL_PollEvent (&event) ) {
			switch (event.type) {

				case SDL_MOUSEMOTION:
					gravity.mouseMoved(event);
					break;
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
					gravity.mouseButton(event);
					break;
				case SDL_KEYDOWN:
					gravity.keyDown(event);
					if (event.key.keysym.sym == SDLK_q && (event.key.keysym.mod & KMOD_LMETA || event.key.keysym.mod & KMOD_RMETA)) {
						done = 1;
					}
					break;
				case SDL_KEYUP:
					gravity.keyUp(event);
					break;
				case SDL_QUIT:
					done = 1;
					break;
				default:
					break;
			}
		}
		
		gravity.update(delta);
		SDL_Delay(10);
        drawGL();
        SDL_GL_SwapBuffers();
	}
}

int main(int argc, char *argv[]) {

	// Init SDL video subsystem
	if ( SDL_Init (SDL_INIT_VIDEO) < 0 ) {
		
        fprintf(stderr, "Couldn't initialize SDL: %s\n",
			SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

    // Set GL context attributes
    initAttributes ();
    
    // Create GL context
    createSurface(0);
    
    // Get GL context attributes
    printAttributes();
    
    // Init GL state
    initGL();
    
    // Draw, get events...
    mainLoop();
    
    // Cleanup
	SDL_Quit();
	
    return 0;
}
