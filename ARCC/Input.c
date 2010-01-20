#include "Input.h"

// sets keyboard repeat on or off
void ARC_InputSetKeyboardRepeat(bool onoff)
{
	if(onoff == true)
	{
		// Enable auto repeat for keyboard input
		SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	}
	else
	{
		// Disable auto repeat for keyboard input
		SDL_EnableKeyRepeat(0, 0);
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                      PUBLIC INTERFACE
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// clear's input, gets current modifiers, enables unicode and disables key repeat
void ARC_InputInit(ARC_Input *i, bool keyRepeat)
{
	// focus is true unless otherwise set
	i->focus = true;

	// clear keyboard and mouse
	i->keyboard.ARC_MouseClear();
	i->mouse.ARC_MouseClear();

	// Enable UNICODE translation for keyboard input
	SDL_EnableUNICODE(1);

	// set keyboard repeat state
	ARC_InputSetKeyboardRepeat(keyRepeat);
}

/// implementation just for symmetry, does not do anything
void ARC_InputQuit(ARC_Input *i)
{
}

/// returns the full KeyStatus information for the key
KeyStatus ARC_InputGetKeyStatus(ARC_Input *i, int keyNum) { return i->keyboard.status[keyNum]; }
/// test if is set
bool isSet(int state, int flag) { return 0 != (state & flag); }

/// returns true when key has gone from up to down between calls to process
bool ARC_InputIsKeyPressed(ARC_Input *i, int keyNum) { return isSet(i->keyboard.status[keyNum], KeyStatus.PRESSED);   }
/// returns true when key has gone from down to up between calls to process
bool ARC_InputIsKeyReleased(ARC_Input *i, int keyNum) { return isSet(i->keyboard.status[keyNum], KeyStatus.RELEASED);  }
/// returns true when key is physically down
bool ARC_InputIsKeyDown(ARC_Input *i, int keyNum) { return isSet(i->keyboard.status[keyNum], KeyStatus.DOWN);  }
/// returns true when key is physically up
bool ARC_InputIsKeyUp(ARC_Input *i, int keyNum) { return !isSet(i->keyboard.status[keyNum], KeyStatus.DOWN);  }

/// returns true if user has hit a character on the keyboard between two calls to process
bool ARC_InputIsCharHit(ARC_Input *i)           { return ARC_KeyboardIsCharHit(i->keyboard);       }
/// returns characters hit by the user between two process calls
char* ARC_InputGetLastChars(ARC_Input *i)         { return i->keyboard.lastChars;      }


//
// mouse query methods
//

/// returns full KeyStatus information for the button
KeyStatus ARC_InputGetMouseButtonStatus(ARC_Input *i, int keyNum) { return i->mouse.buttonStatus[keyNum]; }

/// returns true if mouse button has gone from up to down between calls to process
bool ARC_InputGetMouseButtonPressed(ARC_Input *i, int keyNum) { return isSet(i->mouse.buttonStatus[keyNum], KeyStatus.PRESSED); }
/// returns true if mouse button has gone from down to up between calls to process
bool ARC_InputGetMouseButtonReleased(ARC_Input *i, int keyNum) { return isSet(i->mouse.buttonStatus[keyNum], KeyStatus.RELEASED); }
/// returns true if user holds mouse button down
bool ARC_InputGetMouseButtonDown(ARC_Input *i, int keyNum)  { return isSet(i->mouse.buttonStatus[keyNum], KeyStatus.DOWN); }
/// returns true if user doesn't hold mouse button down
bool ARC_InputGetMouseButtonUp(ARC_Input *i, int keyNum)  { return !isSet(i->mouse.buttonStatus[keyNum], KeyStatus.DOWN); }


// NOTE: for the arc 2D game engine, mouse.x and mouse.y are only used
//       to help determine the virtual coordinates.
//       for 3D games, you may want to use mouse.x and mouse.y
//       but for 2D games, there is never a need to, so mouseX and mouseX2D
//       will return the same values

/// mouseX position
ARCFL ARC_InputGetMouseX(ARC_Input *i)               { return i->mouse.x2D;      }
/// mouseY position
ARCFL ARC_InputGetMouseY(ARC_Input *i)               { return i->mouse.y2D;      }
/// mouse position
ARC_Point ARC_InputGetMousePos(ARC_Input *i) { return Point(i->mouse.x2D, i->mouse.y2D); }
/// old mouse X position
ARCFL ARC_InputGetMouseOldX(ARC_Input *i)            { return i->mouse.oldX2D;   }
/// old mouse Y position
ARCFL ARC_InputGetMouseOldY(ARC_Input *i)            { return i->mouse.oldY2D;   }
/// old mouse position
ARC_Point ARC_InputGetMouseOldPos(ARC_Input *i) { return Point(i->mouse.oldX2D, i->mouse.oldY2D); }

/// returns true when mouse is moving
bool ARC_InputGetMouseMotion(ARC_Input *i)          { return i->mouse.moving; }

/// set mouse cursor visibility
void ARC_InputShowCursor(ARC_Input *i, bool argV) { i->mouse.ARC_MouseSetVisible(argV); }

/// returns true when mouse is wheeling up
bool ARC_InputGetWheelUp(ARC_Input *i)     { return isSet(i->mouse.buttonStatus[WHEELUP], KeyStatus.DOWN);   }
/// returns true when mouse is wheeling down
bool ARC_InputGetWheelDown(ARC_Input *i)   { return isSet(i->mouse.buttonStatus[WHEELDOWN], KeyStatus.DOWN); }

//
// other methods
//

/// return whether SDL window has focus
bool ARC_InputGetFocus(ARC_Input *i) { return i->focus; }

/// force quit of application
void ARC_InputForceQuit(ARC_Input *i) { i->keyboard.status[ARC_QUIT] = KeyStatus.DOWN | KeyStatus.PRESSED; }

/// returns true if quitting
bool ARC_InputIsQuit(ARC_Input *i) { return (i->keyboard.status[ARC_QUIT] & KeyStatus.DOWN) != 0; }

/// Capture input from user
void ARC_InputProcess(ARC_Input *i)
{
	SDL_Event event;

	i->mouse.moving = false;
	i->mouse.ARC_MouseClearHit();
	i->keyboard.ARC_MouseClearHit();

	// Keep on looping through our event until all events are accounted for
	while (SDL_PollEvent(&event))
	{
		// hand the event over to whoever wants it (for now, hybrid's input)
		eventSignal(event);

		// get the type of event
		switch (event.type)
		{
			case SDL_ACTIVEEVENT:
				if ( event.active.gain == 0 )
					focus = false;
				else
					focus = true;
			break;

			case SDL_MOUSEBUTTONUP:
				// clear mouse keys when button up
				i->mouse.ARC_MouseProcessButtonUp(event.button);
			break;

			case SDL_MOUSEBUTTONDOWN:
				// handle mouse keys when button is down
				i->mouse.ARC_MouseProcessButtonDown(event.button);
			break;

			case SDL_MOUSEMOTION:
				// handle mouse motion
				i->mouse.ARC_MouseProcessMotion(event);
			break;

			case SDL_KEYDOWN:
				// handle key down
				i->keyboard.ARC_KeyboardProcessKeyDown(event.key);
			break;

			case SDL_KEYUP:
				// handle key up, release keys
				i->keyboard.handleKeyUp(event.key);
			break;

			case SDL_QUIT:
				// set our SDL quit key to true
				i->keyboard.status[SDL_QUIT] = KeyStatus.DOWN | KeyStatus.PRESSED;
			break;

			case SDL_VIDEORESIZE:
				// have the window be resized based upon user input
				//ARC_WindowResize(wnd, event.resize.w, event.resize.h);

				// reload windows textures because Windows is special
				// and re-initialize OpenGL
				//version(Windows)
				//{
					//arc.gfx.texture.reload();
				//}
			break;

			default:
			break;
		} // switch(event)
	} // while(SDL_Poll(&event))

} // process()
