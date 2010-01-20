
#include "Keyboard.h"


/*******************************************************************************

		Set all keys in keyboard down

*******************************************************************************/
void ARC_KeyboardClearHit(ARC_Keyboard *k)
{
		charHit = false;
		lastChars.length = 0;
		for (int i = 0; i < ARC_LAST; i++)
			status[i] &= KeyStatus.DOWN;
}

/*******************************************************************************

		clear all data inside this structure

*******************************************************************************/
void ARC_KeyboardClear(ARC_Keyboard *k)
{
		ARC_KeyboardSetKeysDown();
		for (int i = 0; i < ARC_LAST; i++)
			status[i] = KeyStatus.UP;
}

/*******************************************************************************

		Handle keyboard when keys are pressed

*******************************************************************************/
void ARC_KeyboardProcessKeyDown(ARC_Keyboard *k, SDL_KeyboardEvent *event)
{
	// evaluate if this does make sense
	status[ANYKEY] |= KeyStatus.DOWN | KeyStatus.PRESSED; // anykey hit

	// set 'down' and 'pressed' bits
	status[event.keysym.sym] |= KeyStatus.DOWN | KeyStatus.PRESSED;

	charHit = true;

	if ( event.keysym.unicode ) // if character needs to be translated
	{
		lastChars = strcat(lastChars,  (char)(event.keysym.unicode)); // store the translated character
	}
}

/*******************************************************************************

		Handle keyboard when keys are released

*******************************************************************************/
void ARC_KeyboardProcessKeyUp(ARC_Keyboard *k, SDL_KeyboardEvent *event)
{
	// evaluate if this does make sense
	status[ANYKEY] |= KeyStatus.UP | KeyStatus.RELEASED; // some key was released

	// unset 'down' bit, set the 'released' bit
	status[event.keysym.sym] &= KeyStatus.PRESSED | KeyStatus.RELEASED;
	status[event.keysym.sym] |= KeyStatus.RELEASED;

	// emit signal
	arc.internals.input.signals.signals.keyUp(event.keysym.sym);
}
