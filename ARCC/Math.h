/**
    \file Math.h
    \brief

    Useful math functions
*/
#ifndef _ARC_MATH_H_
#define _ARC_MATH_H_

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "Types.h"
#include "Point.h"

#ifdef __cplusplus
extern "C" {
#endif

void ARC_MathInit();

/// converts an angle in DEGREES to RADIANS
RADIANS ARC_MathDegreesToRadians(DEGREES deg);
/// converts an angle in RADIANS to DEGREES
DEGREES ARC_MathRadiansToDegrees(RADIANS rad);

/// restricts an angle to the 0 - 360 range
DEGREES ARC_MathRestrictDegree(DEGREES deg);

/// restricts an angle to the 0 - 2PI range
RADIANS ARC_MathRestrictRadian(RADIANS rad);
/*******************************************************************************

   See if number is in range of target, rangle is variable, use with caution

*******************************************************************************/
bool ARC_MathWithinRange(ARCFL argNum, ARCFL argTarget, ARCFL argRange);
/*******************************************************************************

   Calculate the distance between 2 points

*******************************************************************************/
ARCFL ARC_MathDistance(ARC_Point *p1, ARC_Point *p2);
/*******************************************************************************

   Returns the next power of two

*******************************************************************************/
int ARC_MathNextPowerOfTwo(int a);
/*******************************************************************************

   Returns a random integer between a and b

*******************************************************************************/
int ARC_MathRandomRange(ARCFL a, ARCFL b);

/// Finds the roots
bool ARC_MathFindRoots(ARCFL a, ARCFL b, ARCFL c, ARCFL* t0, ARCFL* t1);


/// area of a polygon
ARCFL ARC_MathArea(ARC_Point* contour, int len);
/// Max distance of a given point from a given set of points
ARCFL ARC_MathMaxDistance(ARC_Point* given, ARC_Point* set, int setLength);

/// swap ARCFL values
void ARC_MathSwapf(ARCFL* a, ARCFL* b);

/// clamp ARCFL value to min and max
ARCFL ARC_MathClampf(ARCFL x, ARCFL min, ARCFL max);

/// wrap ARCFL value around min and max
ARCFL ARC_MathWrapf(ARCFL x, ARCFL min, ARCFL max);

/// return sign of a number
ARCFL ARC_MathSignf(ARCFL x);

/// Random number in range [-1,1]
ARCFL ARC_MathRandom();

#ifdef __cplusplus
}
#endif

#endif
