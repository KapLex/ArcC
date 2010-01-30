#include "ARCC/ARC.h"

// main is just here to handle states
int main()
{
	ARC_Window wnd;
	ARC_Size sz = {800, 600};
	ARC_WindowInit(&wnd, "Window example", &sz, false, true);

	ARC_Input input;
	ARC_InputInit(&input, true);

	ARC_LogInit("stdout");

	// main loop
	while (!ARC_InputIsKeyPressed(&input, ARC_QUIT))
	{
		// clear the screen before drawing
		ARC_WindowClear(&wnd);
		ARC_InputProcess(&input);

		// user lightly taps 't' key
		if (ARC_InputIsKeyPressed(&input, 't'))
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "T key pressed");
		}

		// user holds down 't' key
		if (ARC_InputIsKeyDown(&input, 's'))
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "S key pressed");
		}

		// user lightly clicks right mouse button
		if (ARC_InputIsMouseButtonPressed(&input, RIGHT))
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "Mouse button RIGHT pressed");
		}

		// user holds down left mouse button
		if (ARC_InputIsMouseButtonDown(&input, LEFT)) // RIGHT and MIDDLE work as well
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "Mouse button LEFT pressed");
		}

		// returns true if user hits a character
		if (ARC_InputIsCharHit(&input))
		{
			// returns the last characters the user hit
			ARC_Log(LOG4C_PRIORITY_INFO, input.keyboard.lastChars);
		}

		// returns true if mouse is in motion
		if (ARC_InputIsMouseMoving(&input))
		{
			char *message;

			sprintf(message, "X: %d Y: %d", input.mouse.x, input.mouse.y); 

			ARC_Log(LOG4C_PRIORITY_INFO, message);
		}

		// returns true if mouse is wheeling up
		if (ARC_InputIsWheelUp(&input)) // wheelDown - returns true on mouse Wheelup and Wheeldown
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "Mouse wheel is up");
		}

		// return true if current modifier is down
		if (ARC_InputIsKeyPressed(&input, ARC_LSHIFT)) // RSHIFT, LCTRL, RCTRL, LALT, RALT, LMETA, RMETA, NUM, CAPS
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "LSHIFT mod is hit");
		}

		if (ARC_InputIsKeyDown(&input, ARC_RSHIFT))
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "RSHIFT mod is hit");
		}

	}

	ARC_WindowQuit(&wnd);

	return 0;
}
