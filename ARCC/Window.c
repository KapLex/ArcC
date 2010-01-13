
#include "Window.h"

void setupPixelFormat(void)
{
   SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
   SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
   SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
   SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
   SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
}

void setupPixelDepth(ARC_Window *w)
{
	const SDL_VideoInfo *info = SDL_GetVideoInfo();

	if(info == NULL)
	{
			//throw new Exception("Window: SDL_GetVideoInfo() is null");
	}

	w->bpp = info->vfmt->BitsPerPixel;
}

// Build video flags based on user configuration
Uint32 buildVideoFlags(ARC_Window *w)
{
	// setup video flags
	Uint32 videoFlags = SDL_OPENGL|SDL_HWPALETTE;

	// if user wants screen resizable, set it
	if (w->isResizable)
		videoFlags = videoFlags | SDL_RESIZABLE;

	// user wants fullscreen, set it
	if (w->isFullscreen)
		videoFlags = videoFlags | SDL_FULLSCREEN;

	return videoFlags;
}


void initLog(void)
{
	log4c_category_t* arc = log4c_category_get("arc");
	windowLog = log4c_category_get("arc.window");
	log4c_category_log(arc, LOG4C_PRIORITY_INFO, "Arc initialized");
}

int initSDL(ARC_Window *w)
{
	// initialize video
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//log.fatal("Window: Failed to initialize SDL Video");
		//throw new Exception("Window: Failed to initialize SDL Video");
		return EXIT_FAILURE;
	}

	// set pixel depth and format
	setupPixelDepth(w);
	setupPixelFormat();

	// open SDL window with given video flags
	w->screen = SDL_SetVideoMode(w->width, w->height, w->bpp,  buildVideoFlags(w));

	if (w->screen == NULL)
	{
		//log.fatal("Window: screen is null after SDL_SetVideoMode called");
		//throw new Exception("Window: screen is null after SDL_SetVideoMode called");
		return EXIT_FAILURE;
	}

	// set window caption, for some mysterious reason title info is lost if we don't do toUtfz
	SDL_WM_SetCaption(w->title, NULL);

	return 0;
}

void printVendor(void)
{
	/*
	log.info("Render Type: OpenGL (Hardware)");
	log.info( "Vendor     : " ~ fromStringz(glGetString( GL_VENDOR )) ~ "\n");
	log.info( "Renderer   : " ~  fromStringz(glGetString( GL_RENDERER )) ~ "\n" );
	log.info( "Version    : " ~  fromStringz(glGetString( GL_VERSION )) ~ "\n" );
	log.info( "Extensions : " ~  fromStringz(glGetString( GL_EXTENSIONS )) ~ "\n" );
	*/
}

void setGLStates(void)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
}

void resizeGL(ARC_Window *w)
{
	// viewport
	glViewport(0,0, w->width, w->height);

	// reset the matrices
	//coordinates.setupGLMatrices();

	// states
	setGLStates();
}


// Open Window
int ARC_WindowInit(ARC_Window *w, char *title, int width, int height, int isFS, int isR)
{
	log4c_category_log(windowLog, LOG4C_PRIORITY_INFO, "ARC_WindowInit(...)");

	// init variables
	w->title = title;
	w->width = width;
	w->height = height;
	w->isFullscreen = isFS;
	w->isResizable = isR;

	initLog();

	initSDL(w);

	resizeGL(w);

	return 0;
}

// Exit the app
int ARC_WindowQuit(ARC_Window *w)
{
	SDL_FreeSurface(w->screen);
	SDL_Quit();
	log4c_fini();
	return 0;
}

//	Resize window to desired width and height
int ARC_WindowResize(ARC_Window *wnd, int argWidth, int argHeight)
{
	wnd->width = argWidth;
	wnd->height = argHeight;

	if (wnd->isFullscreen == true)
		wnd->screen = SDL_SetVideoMode(argWidth, argHeight, wnd->bpp, SDL_OPENGL|SDL_HWPALETTE|SDL_FULLSCREEN|SDL_RESIZABLE);
	else
		wnd->screen = SDL_SetVideoMode(argWidth, argHeight, wnd->bpp, SDL_OPENGL|SDL_HWPALETTE|SDL_RESIZABLE);

	resizeGL(wnd);

	return 0;
}

///	Toggle between fullscreen and windowed mode; linux only
int ARC_WindowToggleFullScreen(ARC_Window *wnd)
{
	if(SDL_WM_ToggleFullScreen(wnd->screen) == 0)
	{
		//log.error("Window: Failed to toggle fullscreen");
		return 0;
	}

	wnd->isFullscreen = !wnd->isFullscreen;
	return wnd->isFullscreen;

	return 0;
}

int ARC_WindowClear(void)
{
	SDL_GL_SwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return 0;
}

//	Captures a screenshot and saves in BMP format to current directory
int ARC_WindowSaveBMP(ARC_Window *wnd, char* argFile)
{
	SDL_Surface *temp=NULL;
	unsigned char *pixels=NULL;
	int i;

	if (!(wnd->screen->flags & SDL_OPENGL))
	{
		SDL_SaveBMP(temp, argFile);
		return 0;
	}

	temp = SDL_CreateRGBSurface(SDL_SWSURFACE, wnd->screen->w, wnd->screen->h, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	0x000000FF, 0x0000FF00, 0x00FF0000, 0
#else
	0x00FF0000, 0x0000FF00, 0x000000FF, 0
#endif
	);
	if (temp == NULL)
		return -1;

	pixels = malloc(3 * wnd->screen->w * wnd->screen->h);
	if (pixels == NULL)
	{
		SDL_FreeSurface(temp);
		return -1;
	}

	glReadPixels(0, 0, wnd->screen->w, wnd->screen->h, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	for (i=0; i<wnd->screen->h; i++)
		memcpy(((char *) temp->pixels) + temp->pitch * i, pixels + 3*wnd->screen->w * (wnd->screen->h-i-1), wnd->screen->w*3);
	free(pixels);

	SDL_SaveBMP(temp, argFile);
	SDL_FreeSurface(temp);

	return 0;
}

// load up SDL

