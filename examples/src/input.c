#include "ARCC/Window.h"
#include "ARCC/Input.h"
#include "ARCC/Log.h"

// main is just here to handle states
int main()
{
	ARC_Window wnd;
	ARC_Size sz = {800, 600};
	ARC_WindowInit(&wnd, "Window example", &sz, false, true);

	ARC_Input input;
	ARC_InputInit(&input);

	ARC_InitLogger("stdout");

	// main loop
	while (!arc.input.keyPressed(ARC_QUIT))
	{
		// clear the screen before drawing
		ARC_WindowClear(&wnd);
		ARC_InputProcess(&input);

		// user lightly taps 't' key
		if (ARC_InputKeyPressed(&input, 't'))
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "T key pressed");
		}

		// user holds down 't' key
		if (arc.input.keyDown('s'))
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "S key pressed");
		}

		// user lightly clicks right mouse button
		if (arc.input.mouseButtonPressed(RIGHT))
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "Mouse button RIGHT pressed");
		}

		// user holds down left mouse button
		if (arc.input.mouseButtonDown(LEFT)) // RIGHT and MIDDLE work as well
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "Mouse button LEFT pressed");
		}

		// returns true if user hits a character
		if (arc.input.charHit)
		{
			// returns the last characters the user hit
			ARC_Log(LOG4C_PRIORITY_INFO, input.keyboard.lastChars);
		}

		// returns true if mouse is in motion
		if (ARC_InputIsMouseMoving(&input))
		{
			char *message = "X: ";
			strcat(message, itoa(input.mouse.x));
			strcat(message, " Y: ");
			strcat(message, itoa(input.mouse.y));

			ARC_Log(LOG4C_PRIORITY_INFO, message);
		}

		// returns true if mouse is wheeling up
		if (ARC_InputIsWheelUp(&input)) // wheelDown - returns true on mouse Wheelup and Wheeldown
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "Mouse wheel is up");
		}

		// return true if current modifier is down
		if (ARC_InputIsKeyPressed(ARC_LSHIFT)) // RSHIFT, LCTRL, RCTRL, LALT, RALT, LMETA, RMETA, NUM, CAPS
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "LSHIFT mod is hit");
		}

		if (arc.input.keyDown(ARC_RSHIFT))
		{
			ARC_Log(LOG4C_PRIORITY_INFO, "RSHIFT mod is hit");
		}

	}

	ARC_WindowQuit(&wnd);

	return 0;
}
