
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
		log4c_category_log(windowLog, LOG4C_PRIORITY_ERROR, "Failed to initialize SDL Video");
		return ARC_WINDOW_VIDEO_INIT;
	}

	// set pixel depth and format
	setupPixelDepth(w);
	setupPixelFormat();

	// open SDL window with given video flags
	w->screen = SDL_SetVideoMode(w->size->w, w->size->h, w->bpp,  buildVideoFlags(w));

	if (w->screen == NULL)
	{
		//log.fatal("Window: screen is null after SDL_SetVideoMode called");
		//throw new Exception("Window: screen is null after SDL_SetVideoMode called");
		return ARC_SURFACE_IS_NULL;
	}

	// set window caption, for some mysterious reason title info is lost if we don't do toUtfz
	SDL_WM_SetCaption(w->title, NULL);

	logVendor();

	return ARC_SUCCESS;
}

void logVendor(void)
{
	log4c_category_log(windowLog, LOG4C_PRIORITY_INFO, glGetString( GL_VENDOR ));
	log4c_category_log(windowLog, LOG4C_PRIORITY_INFO, glGetString( GL_RENDERER ));
	log4c_category_log(windowLog, LOG4C_PRIORITY_INFO, glGetString( GL_VERSION ));
	log4c_category_log(windowLog, LOG4C_PRIORITY_INFO, glGetString( GL_EXTENSIONS ));
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
	int originX = 0, originY = 0;

	// viewport
	glViewport(0,0, w->size->w, w->size->h);

	// projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(originX, originX + w->size->w, originY + w->size->h, originY, -1.0f, 1.0f);

	// modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// states
	setGLStates();
}


// Open Window
int ARC_WindowInit(ARC_Window *w, char *title, ARC_Size* size, int isFS, int isR)
{
	log4c_category_log(windowLog, LOG4C_PRIORITY_INFO, "ARC_WindowInit(...)");

	// init variables
	w->title = title;
	w->size = size;
	w->isFullscreen = isFS;
	w->isResizable = isR;

	initLog();

	int initSuccess = initSDL(w);
	if (!initSuccess) return initSuccess;

	resizeGL(w);

	return ARC_SUCCESS;
}

// Exit the app
int ARC_WindowQuit(ARC_Window *w)
{
	SDL_FreeSurface(w->screen);
	SDL_Quit();
	log4c_fini();
	return ARC_SUCCESS;
}

//	Resize window to desired width and height
int ARC_WindowResize(ARC_Window *wnd, ARC_Size* size)
{
	wnd->size = size;

	if (wnd->isFullscreen == true)
		wnd->screen = SDL_SetVideoMode(size->w, size->h, wnd->bpp, SDL_OPENGL|SDL_HWPALETTE|SDL_FULLSCREEN|SDL_RESIZABLE);
	else
		wnd->screen = SDL_SetVideoMode(size->w, size->h, wnd->bpp, SDL_OPENGL|SDL_HWPALETTE|SDL_RESIZABLE);

	resizeGL(wnd);

	return ARC_SUCCESS;
}

///	Toggle between fullscreen and windowed mode; linux only
bool ARC_WindowToggleFullScreen(ARC_Window *wnd)
{
	if(SDL_WM_ToggleFullScreen(wnd->screen) == 0)
	{
		//log.error("Window: Failed to toggle fullscreen");
		return ARC_WINDOW_TOGGLE;
	}

	wnd->isFullscreen = !wnd->isFullscreen;

	return wnd->isFullscreen;
}

int ARC_WindowClear(ARC_Window *wnd)
{
	SDL_GL_SwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	return ARC_SUCCESS;
}

//	Captures a screenshot and saves in BMP format to current directory
int ARC_WindowSaveBMP(ARC_Window *wnd, char* argFile)
{
	SDL_Surface *temp=NULL;
	unsigned char *pixels=NULL;
	int i;

	temp = SDL_CreateRGBSurface(SDL_SWSURFACE, wnd->screen->w, wnd->screen->h, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	0x000000FF, 0x0000FF00, 0x00FF0000, 0
#else
	0x00FF0000, 0x0000FF00, 0x000000FF, 0
#endif
	);

	if (temp == NULL)
	{
		return ARC_SURFACE_IS_NULL;
	}

	pixels = malloc(3 * wnd->screen->w * wnd->screen->h);
	if (pixels == NULL)
	{
		SDL_FreeSurface(temp);
		return ARC_SURFACE_IS_NULL;
	}

	glReadPixels(0, 0, wnd->screen->w, wnd->screen->h, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	for (i=0; i<wnd->screen->h; i++)
		memcpy(((char *) temp->pixels) + temp->pitch * i, pixels + 3*wnd->screen->w * (wnd->screen->h-i-1), wnd->screen->w*3);
	free(pixels);

	SDL_SaveBMP(temp, argFile);
	SDL_FreeSurface(temp);

	return ARC_SUCCESS;
}

