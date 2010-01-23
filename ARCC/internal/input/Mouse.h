/**
    \file Mouse.h
    \brief

    Internal mouse functions
*/

#ifndef _ARC_MOUSE_H_
#define _ARC_MOUSE_H_

#include <stdbool.h>
#include <SDL/SDL.h>
#include "../../Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************

	Mouse structure to hold all the information in a mouse.

*******************************************************************************/
typedef struct ARC_Mouse
{
	/**
		The first set of coordinates, 'real world' coordinates, are used to tell
		where the mouse is no matter the size of the window.
	**/
	int x, y;
	int oldX, oldY;

	/**
		The '2D' coordinates, aka virtual coordinates, stay the same relative to the
		window, so the window can be resized and the relative coordinates stay the
		same, making them good for 2D gui's.
	**/
	ARCFL x2D, y2D;
	ARCFL oldX2D, oldY2D;

	/**
		The next bool tells us whether or not the mouse has been moving. It is useful
		so you can say, that if the mouse is moving, move a window with it.
	**/
	bool moving;

	/// array of button information
	enum KeyStatus buttonStatus[MAXMOUSEBUTTON];
} ARC_Mouse;

/// set default cursor visibility
void ARC_MouseSetVisible(ARC_Mouse *m, bool argV);
/*******************************************************************************

	Properly handle mouse motion

	NOTE: 	Virtual coordinates make it so a smaller or bigger window
			keeps the same relative mouse coordinates, whether it be 800x600 or
			anything else they are used so you can click on gui objects when they
			are resized by OpenGL.

*******************************************************************************/
void ARC_MouseProcessMotion(ARC_Mouse *m, SDL_Event* event);

/*******************************************************************************

		Clear all data in the hit bool array

*******************************************************************************/
void ARC_MouseClearHit(ARC_Mouse *m);

/*******************************************************************************

		Clear all data in the button

*******************************************************************************/
void ARC_MouseClear(ARC_Mouse *m);


/*******************************************************************************

		Properly handle mouse when mouse is down

*******************************************************************************/
void ARC_MouseProcessButtonDown(ARC_Mouse *m, SDL_MouseButtonEvent* event);

/*******************************************************************************

		Properly handle mouse when button goes up

*******************************************************************************/
void ARC_MouseProcessButtonUp(ARC_Mouse *m, SDL_MouseButtonEvent* event);

#ifdef __cplusplus
}
#endif

#endif
