#include "ARCC/Window.h"
#include "ARCC/Input.h"
#include "ARCC/Log.h"

// main is just here to handle states
int main()
{
	ARC_Window wnd;
	ARC_Size sz = {800, 600};

	ARC_LogInit("stdout");
	ARC_WindowInit(&wnd, "Window example", &sz, false, true);

	ARC_Input input;
	ARC_InputInit(&input, true);

	// main loop
	while (!ARC_InputIsKeyPressed(&input, ARC_QUIT))
	{
		// clear the screen before drawing
		ARC_WindowClear(&wnd);

		ARC_InputProcess(&input);
	}

	ARC_WindowQuit(&wnd);

	return 0;
}
