#include "Mouse.h"

/// set default cursor visibility
void ARC_MouseSetVisible(bool argV)
{
	if(argV)
		SDL_ShowCursor(SDL_ENABLE);
	else
		SDL_ShowCursor(SDL_DISABLE);
}

/*******************************************************************************

	Properly handle mouse motion

	NOTE: 	Virtual coordinates make it so a smaller or bigger window
			keeps the same relative mouse coordinates, whether it be 800x600 or
			anything else they are used so you can click on gui objects when they
			are resized by OpenGL.

*******************************************************************************/
void ARC_MouseProcessMotion(ARC_Mouse *m, SDL_Event* event)
{
	m->moving = true;

	m->oldX = x;
	m->oldY = y;

	m->x = event.button.x;
	m->y = event.button.y;

	m->oldX2D = x2D;
	m->oldY2D = y2D;

	m->x2D = x/(arc.window.getWidth/arc.window.coordinates.getWidth) + arc.window.coordinates.getOrigin.x;
	m->y2D = y/(arc.window.getHeight/arc.window.coordinates.getHeight) + arc.window.coordinates.getOrigin.y;
}


/*******************************************************************************

		Clear all data in the hit bool array

*******************************************************************************/
void ARC_MouseClearHit(ARC_Mouse *m)
{
	for (int i = 0; i < MAXMOUSEBUTTON; ++i)
		m->buttonStatus[i] &= KeyStatus.DOWN;
}


/*******************************************************************************

		Clear all data in the button

*******************************************************************************/
void ARC_MouseClear(ARC_Mouse *m)
{
	for (int i = 0; i < MAXMOUSEBUTTON; ++i)
		m->buttonStatus[i] = KeyStatus.UP;
}


/*******************************************************************************

		Properly handle mouse when mouse is down

*******************************************************************************/
void ARC_MouseProcessButtonDown(ARC_Mouse *m, SDL_MouseButtonEvent* event)
{
	// if the button is already down, nothing needs to be done
	if(m->buttonStatus[event.button] & KeyStatus.DOWN != 0)
		return;

	// any button was hit
	m->buttonStatus[ANYBUTTON] |= KeyStatus.PRESSED;

	// set the 'down' and 'pressed' bits
	m->buttonStatus[event.button] |= KeyStatus.DOWN | KeyStatus.PRESSED;
}

/*******************************************************************************

		Properly handle mouse when button goes up

*******************************************************************************/
void ARC_MouseProcessButtonUp(ARC_Mouse *m, SDL_MouseButtonEvent* event)
{
	// if the button is already up, nothing needs to be done
	if(m->buttonStatus[event.button] & KeyStatus.DOWN == 0)
		return;

	// any button was released
	m->buttonStatus[ANYBUTTON] |= KeyStatus.RELEASED;

	// unset 'down' bit, set the 'released' bit
	m->buttonStatus[event.button] &= KeyStatus.PRESSED | KeyStatus.RELEASED;
	m->buttonStatus[event.button] |= KeyStatus.RELEASED;
}
