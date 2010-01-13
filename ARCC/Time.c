
#include "Time.h"


void ARC_TimeProcess(ARC_Time *t)
{
	if(t->currTime == 0)
	{
		t->currTime = SDL_GetTicks();
		t->prevTime = t->currTime - 1;
	}

	t->prevTime = t->currTime;
	t->currTime = SDL_GetTicks();

	t->frames++;

	t->msPassed += (t->currTime - t->prevTime);

	if(t->msPassed > 1000)
	{
		t->fps = t->frames;
		t->frames = 0;
		t->msPassed = 0;
	}
}

// stop execution for some milliseconds
void ARC_TimeSleep(unsigned int milliseconds)
{
	SDL_Delay(milliseconds);
}

// gets the number of milliseconds passed between two calls to process
uint Arc_TimeGetElapsed(ARC_Time *t)
{
	return t->currTime - t->prevTime;
}

// number of seconds passed between two calls to process
double ARC_TimeGetElapsedSec(ARC_Time *t)
{
	return Arc_TimeGetElapsed(t) / 1000.;
}

// frames per second the application is currently receiving
unsigned int ARC_TimeGetFPS(ARC_Time *t)
{
	return t->fps;
}

void ARC_LimitFPS(ARC_Time *t, int maxFps)
{
	if (maxFps <= 0) { return; }

	int targetMsPerFrame = 1000 / maxFps;
	uint cTime = SDL_GetTicks();

	int sleepAmount = targetMsPerFrame - (cTime - t->currTime);

	if(sleepAmount <= 0)
		return;

	ARC_TimeSleep(sleepAmount);
}
