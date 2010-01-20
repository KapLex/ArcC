/** \file Time.h
    \brief

    Interface for time functions
*/

#ifndef _ARC_TIME_H_
#define _ARC_TIME_H_

// Std
#include <stdbool.h>
#include <string.h>

// SDL + GL
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Time struct
 */
typedef struct ARC_Time
{
    // current time
	unsigned int currTime;
    // previous time
	unsigned int  prevTime;

	// FPS
	unsigned int  fps;

	// helpers for fps calculation
	unsigned int  frames;
	unsigned int  msPassed;
} ARC_Time;

/**
	Calculates fps and captures start of frame time.
	Call at the start of the frame loop.

	\param Time struct
*/
void ARC_TimeProcess(ARC_Time *t);

/**
 * Sleep
 * \param Sleep amount in milliseconds
 */
void ARC_TimeSleep(unsigned int milliseconds);

/**
 * Gets the number of milliseconds passed between two calls to process
 *
 * \param Time struct
 */
unsigned int Arc_TimeGetElapsed(ARC_Time *t);

/**
 * Number of seconds passed between two calls to process
 *
 * \param Time struct
 */
double ARC_TimeGetElapsedSec(ARC_Time *t);

/**
 * Frames per second the application is currently receiving
 *
 * \param Time struct
 */
unsigned int ARC_TimeGetFPS(ARC_Time *t);

/**
 * 	Call at the end of the frame loop in order to limit the
 *	fps to a certain amount.
 *
 *	\param Limit FPS to this number
 */
void ARC_TimeLimitFPS(ARC_Time *t, int maxFps);

#ifdef __cplusplus
}
#endif


#endif
