/** \file Input.h
    \brief

    Input wrapper that sits on SDL
*/

#ifndef _ARC_INPUT_H_
#define _ARC_INPUT_H_

// Std
#include <stdbool.h>
#include <string.h>

// Log4c
#include <log4c.h>

// SDL + GL
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#include "Types.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Point.h"

#ifdef __cplusplus
extern "C" {
#endif

log4c_category_t* inputLog;

typedef struct ARC_Input
{
	bool focus;
	ARC_Keyboard keyboard;
	ARC_Mouse mouse;
} ARC_Input;


// sets keyboard repeat on or off
void ARC_InputSetKeyboardRepeat(bool onoff);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                      PUBLIC INTERFACE
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// clear's input, gets current modifiers, enables unicode and disables key repeat
void ARC_InputInit(ARC_Input *i, bool keyRepeat);

/// implementation just for symmetry, does not do anything
void ARC_InputQuit(ARC_Input *i);

//
// keyboard configuration methods
//



//
// keyboard query methods
//

/// returns the full KeyStatus information for the key
enum KeyStatus ARC_InputGetKeyStatus(ARC_Input *i, int keyNum);

/// returns true when key has gone from up to down between calls to process
bool ARC_InputIsKeyPressed(ARC_Input *i, int keyNum);
/// returns true when key has gone from down to up between calls to process
bool ARC_InputIsKeyReleased(ARC_Input *i, int keyNum);
/// returns true when key is physically down
bool ARC_InputIsKeyDown(ARC_Input *i, int keyNum);
/// returns true when key is physically up
bool ARC_InputIsKeyUp(ARC_Input *i, int keyNum);

/// returns true if user has hit a character on the keyboard between two calls to process
bool ARC_InputIsCharHit(ARC_Input *i);
/// returns characters hit by the user between two process calls
char* ARC_InputGetLastChars(ARC_Input *i);


//
// mouse query methods
//

/// returns full KeyStatus information for the button
enum KeyStatus ARC_InputGetMouseButtonStatus(ARC_Input *i, int keyNum);

/// returns true if mouse button has gone from up to down between calls to process
bool ARC_InputGetMouseButtonPressed(ARC_Input *i, int keyNum);
/// returns true if mouse button has gone from down to up between calls to process
bool ARC_InputGetMouseButtonReleased(ARC_Input *i, int keyNum);
/// returns true if user holds mouse button down
bool ARC_InputGetMouseButtonDown(ARC_Input *i, int keyNum);
/// returns true if user doesn't hold mouse button down
bool ARC_InputGetMouseButtonUp(ARC_Input *i, int keyNum);


// NOTE: for the arc 2D game engine, mouse.x and mouse.y are only used
//       to help determine the virtual coordinates.
//       for 3D games, you may want to use mouse.x and mouse.y
//       but for 2D games, there is never a need to, so mouseX and mouseX2D
//       will return the same values

/// mouseX position
ARCFL ARC_InputGetMouseX(ARC_Input *i);
/// mouseY position
ARCFL ARC_InputGetMouseY(ARC_Input *i);
/// mouse position
ARC_Point ARC_InputGetMousePos(ARC_Input *i);
/// old mouse X position
ARCFL ARC_InputGetMouseOldX(ARC_Input *i);
/// old mouse Y position
ARCFL ARC_InputGetMouseOldY(ARC_Input *i);
/// old mouse position
ARC_Point ARC_InputGetMouseOldPos(ARC_Input *i);

/// returns true when mouse is moving
bool ARC_InputGetMouseMotion(ARC_Input *i);

/// set mouse cursor visibility
void ARC_InputShowCursor(ARC_Input *i, bool argV);

/// returns true when mouse is wheeling up
bool ARC_InputGetWheelUp(ARC_Input *i);
/// returns true when mouse is wheeling down
bool ARC_InputGetWheelDown(ARC_Input *i);

/// return whether SDL window has focus
bool ARC_InputGetFocus(ARC_Input *i);

/// force quit of application
void ARC_InputForceQuit(ARC_Input *i);

/// returns true if quitting
bool ARC_InputIsQuit(ARC_Input *i);

/// Capture input from user
void ARC_InputProcess(ARC_Input *i);


#ifdef __cplusplus
}
#endif


#endif
