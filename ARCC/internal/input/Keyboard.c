
#include "Keyboard.h"


/*******************************************************************************

		Set all keys in keyboard down

*******************************************************************************/
void ARC_KeyboardClearHit(ARC_Keyboard *k)
{
		k->charHit = false;
		k->lastChars = NULL;
		for (int i = 0; i < ARC_LAST; i++)
			k->status[i] &= DOWN;
}

/*******************************************************************************

		clear all data inside this structure

*******************************************************************************/
void ARC_KeyboardClear(ARC_Keyboard *k)
{
		ARC_KeyboardSetKeysDown(k);
		for (int i = 0; i < ARC_LAST; i++)
			k->status[i] = UP;
}

/*******************************************************************************

		Handle keyboard when keys are pressed

*******************************************************************************/
void ARC_KeyboardProcessKeyDown(ARC_Keyboard *k, SDL_KeyboardEvent *event)
{
	// evaluate if this does make sense
	k->status[ARC_ANYKEY] |= DOWN | PRESSED; // ARC_ANYKEY hit

	// set 'down' and 'pressed' bits
	k->status[event->keysym.sym] |= DOWN | PRESSED;

	k->charHit = true;

	if ( event->keysym.unicode ) // if character needs to be translated
	{
		strcat(k->lastChars,  (char)(event->keysym.unicode)); // store the translated character
	}
}

/*******************************************************************************

		Handle keyboard when keys are released

*******************************************************************************/
void ARC_KeyboardProcessKeyUp(ARC_Keyboard *k, SDL_KeyboardEvent *event)
{
	// evaluate if this does make sense
	k->status[ARC_ANYKEY] |= UP | RELEASED; // some key was released

	// unset 'down' bit, set the 'released' bit
	k->status[event->keysym.sym] &= PRESSED | RELEASED;
	k->status[event->keysym.sym] |= RELEASED;
}
