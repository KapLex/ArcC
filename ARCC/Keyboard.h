/**
    \file Keyboard.h
    \brief

    Internal keyboard processing
*/

#ifndef _ARC_KEYBOARD_H_
#define _ARC_KEYBOARD_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <SDL/SDL.h>

#include "Types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ARC_Keyboard
{
	enum KeyStatus status[ARC_LAST];

	/// whether any character was hit between two process calls
	bool charHit;

	/// holds the characters hit between two process calls
	char* lastChars;
} ARC_Keyboard;

/*******************************************************************************

		Set all keys in keyboard down

*******************************************************************************/
void ARC_KeyboardClearHit(ARC_Keyboard *k);

/*******************************************************************************

		clear all data inside this structure

*******************************************************************************/
void ARC_KeyboardClear(ARC_Keyboard *k);

/*******************************************************************************

		Handle keyboard when keys are pressed

*******************************************************************************/
void ARC_KeyboardProcessKeyDown(ARC_Keyboard *k, SDL_KeyboardEvent *event);

/*******************************************************************************

		Handle keyboard when keys are released

*******************************************************************************/
void ARC_KeyboardProcessKeyUp(ARC_Keyboard *k, SDL_KeyboardEvent *event);

#ifdef __cplusplus
}
#endif

#endif
