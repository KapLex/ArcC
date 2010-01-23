/**
    \file Point.h
    \brief

    Point structure and functions to act on it
*/

#ifndef _ARC_POINT_H_
#define _ARC_POINT_H_

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/***
  A point structure

  Generally, methods perform actions in-place if possible.
  If the method ends in Copy it's a convenience wrapper for
  copying the vector and then applying the method.

  Freely uses inout arguments for speed reasons.
*/
typedef struct ARC_Point
{
	/** X axis coordinate */
	ARCFL x;
	/** Y Axis coordinate */
	ARCFL y;
} ARC_Point;

#ifdef __cplusplus
}
#endif

#endif
