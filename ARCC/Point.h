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


/// rotate
ARC_Point ARC_PointRotateCopy(ARC_Point *p, RADIANS angle);

///
ARC_Point ARC_PointMakePerpTo(ARC_Point *p);

/*** unfortunately, making this an opCall makes Point(1,1) ambigious...
Point 'constructor' from polar coordinates
*/
ARC_Point ARC_PointFromPolar(ARC_Point *p, ARCFL length, RADIANS angle);


/// scaling product
ARC_Point* ARC_PointScalef(ARC_Point *p, ARCFL by);

ARC_Point* ARC_PointScale(ARC_Point *p, ARC_Point* by);

/** Vector bDot product */
ARCFL ARC_PointDot(ARC_Point *p, ARC_Point *v);

/** Vector bCross product */
ARCFL ARC_PointCross(ARC_Point *p, ARC_Point* v);
/** Scalar cross product */
ARC_Point ARC_PointCrossf(ARC_Point *p, ARCFL s);

/** Scalar addition */
ARC_Point ARC_PointAddf(ARC_Point *p, ARCFL V);

/** Scalar subtraction */
ARC_Point ARC_PointSubf(ARC_Point *p, ARCFL n);

/** Scalar addition */
ARC_Point* ARC_PointAddAssignf(ARC_Point *p, ARCFL V);

/** Scalar subtraction */
ARC_Point* ARC_PointSubAssignf(ARC_Point *p, ARCFL V);

/** Scalar multiplication */
ARC_Point* ARC_PointMulAssignf(ARC_Point *p, ARCFL s);

/** Scalar multiplication */
ARC_Point ARC_PointMulf(ARC_Point *p, ARCFL s);

/** Scalar division */
ARC_Point* ARC_PointDivAssignf(ARC_Point *p, ARCFL s);

/** Scalar division */
ARC_Point ARC_PointDiv(ARC_Point *p, ARCFL s);

/** Vector addition */
ARC_Point* ARC_PointAddAssign(ARC_Point *p, ARC_Point* Other);
///
ARC_Point ARC_PointAdd(ARC_Point *p, ARC_Point* V);
///
ARC_Point* ARC_PointSubAssign(ARC_Point *p, ARC_Point* Other);

///
ARC_Point ARC_PointSub(ARC_Point *p, ARC_Point* V);


/// negation
ARC_Point ARC_PointNeg(ARC_Point *p);
///
ARCFL ARC_PointMagnitude(ARC_Point* p);

/// Get the length squared. For performance, use this instead of
/// Point.length (if possible).
ARCFL ARC_PointLengthSquared(ARC_Point *p);

/// Get the length of this vector (the norm).
ARCFL ARC_PointLength(ARC_Point *p);

/// Convert this vector into a unit vector. Returns the length.
ARCFL ARC_PointNormalize(ARC_Point *p);
///
ARC_Point* ARC_PointNormalizeCopy(ARC_Point *p);
///
ARCFL ARC_PointDistance(ARC_Point *p, ARC_Point* v);

///
ARC_Point ARC_PointPerp(ARC_Point *p);

///
ARC_Point* ARC_PointClampMax(ARC_Point *p, ARCFL max);
///
ARCFL ARC_PointAngle(ARC_Point *p, ARC_Point* v);

ARC_Point ARC_PointRotate(ARC_Point *p, ARC_Point* v);

///
ARC_Point ARC_PointRotatef(ARC_Point *p, ARCFL angle);

///
ARC_Point* ARC_PointRotateAround(ARC_Point *p1, ARC_Point *p2, ARCFL angle);

///
ARC_Point ARC_PointRotateEquals(ARC_Point *p, ARCFL angle);
///
bool ARC_PointIsZero(ARC_Point *p);

ARC_Point ARC_PointRotateLeft90(ARC_Point *p);

ARC_Point ARC_PointRotateRight90(ARC_Point *p);


#ifdef __cplusplus
}
#endif

#endif
