#include "ARCC/Window.h"
#include "ARCC/Input.h"
#include "ARCC/Draw.h"
#include "ARCC/Texture.h"

// main is just here to handle states
int main()
{
	ARC_Window wnd;
	ARC_Size sz = {800, 600};
	ARC_WindowInit(&wnd, "Window example", &sz, false, true);

	ARC_Input input;
	ARC_InputInit(&input, true);

	ARC_Texture t1;
	ARC_Texture t2;
	ARC_TextureOptions opt1, opt2;
	opt1.keep = true;
	opt2.keep = false;

	t1 = ARC_TextureLoad("testbin/penguin.png",&opt1);
	t2 = ARC_TextureLoad("testbin/penguin.png",&opt2);

	ARC_Point pos1 = {0,100};
	ARC_Point pos2 = {100,200};
	ARC_Point zero = {0,0};
	ARC_Point mouse;
	ARC_Point off1, off2;

	ARC_DrawOptions opt;
	opt.detail = 10;
	opt.fill = false;
	opt.fill = &ARC_Red;
	opt.stroke = &ARC_Black;

	ARC_Size s1 = {50,100};

	// main loop
	while (!ARC_InputIsKeyPressed(&input, ARC_QUIT))
	{
		mouse = ARC_InputGetMousePos(&input);
		off1 = ARC_PointAdd(&mouse, &pos1);
		off2 = ARC_PointAdd(&mouse, &pos2);

		// clear the screen before drawing
		ARC_WindowClear(&wnd);
		ARC_InputProcess(&input);

		ARC_DrawPixel(&mouse, &opt);

		ARC_DrawCircle(&off1,25, &opt);

		ARC_DrawLine(&zero,&mouse, &opt);

		ARC_DrawRectangle(&off1, &s1, &opt);

		ARC_DrawImage(&t1, &off2, &s1, &zero, 0, &ARC_White);

		ARC_DrawImageTopLeft(&t2, &mouse, &s1, &ARC_Red);
	}

	ARC_WindowQuit(&wnd);

	return 0;
}
