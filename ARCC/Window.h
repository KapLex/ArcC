/**
    \file Window.h
    \brief

    Code handling a the creation, destruction, etc. of a
    Game Window
*/

#ifndef _ARC_WINDOW_H_
#define _ARC_WINDOW_H_

// Std
#include <stdbool.h>
#include <string.h>

// Log4c
#include <log4c.h>

// SDL + GL
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "Size.h"

#ifdef __cplusplus
extern "C" {
#endif

log4c_category_t* windowLog;

/**
 * A Game Window
 */
typedef struct ARC_Window
{
	/// Window title
	char *title;

	/// Window width and height
	Size size;

	/// Whether or not window is fullscreen
	int isFullscreen;

	/// Whether or not window is resizable
	int isResizable;

	/// Window Bytes per pixel
	int bpp;

	/// SDL Video surface
	SDL_Surface *screen;
} ARC_Window;


/**
 * Open the window
 *
 * \param Window handle
 * \param Window title
 * \param Window height
 * \param Whether Window is fullscreen or not
 * \param Whether Window is resizable or not
 */
int ARC_WindowInit(ARC_Window *w, char *title, Size ws, int isFS, int isR);

/**
 * Resize the window
 *
 * \param Width to resize to
 * \param Height to resize to
 */
int ARC_WindowResize(ARC_Window *w, Size ns);

/**
 * Close the game application
 */
int ARC_WindowQuit(ARC_Window *w);

/**
 * Toggle fullscreen (works on linux only)
 */
bool ARC_WindowToggleFullScreen(ARC_Window *wnd);

/**
 * Captures a screenshot and saves in BMP format to current directory
 */
int ARC_WindowSaveBMP(ARC_Window *wnd, char* argFile);

/**
 * Swap GL Buffers then clear the screen
 */
int ARC_WindowClear(void);

#ifdef __cplusplus
}
#endif


#endif
