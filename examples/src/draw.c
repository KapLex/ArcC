#include "Window.h"
#include "Input.h"
#include "Draw.h"
#include "Texture.h"

// main is just here to handle states
int main()
{
	ARC_Window wnd;
	ARC_Size sz = {800, 600};
	ARC_WindowInit(&wnd, "Window example", &sz, false, true);

	ARC_Input input;
	ARC_InputInit(&input);

	ARC_Texture t1, t2;
	ARC_TextureOptions opt1, opt2;
	opt1.keep = true;
	opt2.keep = false;

	t1 = ARC_TextureLoad("testbin/penguin.png",opt1);
	t2 = ARC_TextureLoad("testbin/penguin.png",opt2);

	ARC_Point pos1 = {0,100};
	ARC_Point pos2 = {100,200};
	ARC_Point zero = {0,0};
	ARC_Point mouse;
	ARC_Point off1, off2;

	ARC_Size s1 = {50,100};

	// main loop
	while (!ARC_InputKeyPressed(&input, ARC_QUIT))
	{
		mouse = ARC_InputGetMousePos(&input);
		off1 = ARC_PointAdd(&mouse, &pos1);
		off2 = ARC_PointAdd(&mouse, &pos2);

		// clear the screen before drawing
		ARC_WindowClear(&wnd);
		ARC_InputProcess(&input);

		ARC_InputDrawPixel(&mouse, ARC_Color.Red);

		ARC_InputDrawCircle(&off1,25, 20, Color.Red, false);

		ARC_InputDrawLine(&zero,&mouse, ARC_Color.Blue);

		ARC_InputDrawRectangle(&off1, &s1, ARC_Color.Blue,true);

		ARC_InputDrawImage(&t1, &off2, &s1, &zero, 0, ARC_Color.White);

		ARC_InputDrawImageTopLeft(&t2, &off2);
	}

	ARC_WindowQuit(&wnd);

	return 0;
}
