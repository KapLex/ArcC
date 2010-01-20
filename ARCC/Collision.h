/**
    \file Collision.h
    \brief

    Simple shape collision checks
*/

#ifndef _ARC_COLLISION_H_
#define _ARC_COLLISION_H_

#include "Point.h"
#include "Size.h"
#include "Math.h"

#ifdef __cplusplus
extern "C" {
#endif

/// whether 2 boxes collide with each other
bool ARC_CollisionBoxBox(ARC_Point* pos1, ARC_Size* size1, ARC_Point* pos2, ARC_Size* size2);

/// whether a box and circle collide with each other
bool ARC_CollisionBoxCircle(ARC_Point* boxPos, ARC_Size* boxSize, ARC_Point* circlePos, ARCFL radius);

/// determine whether x and y are within given box
bool ARC_CollisionBoxXY(ARC_Point* point, ARC_Point* boxPos, ARC_Size* boxSize);

// CIRCLES ///////////////////////////////////////////////////////////

/// determines whether or not 2 circles have collided
bool ARC_CollisionCircleCircle(	ARC_Point* c1, ARCFL rad1, ARC_Point* c2, ARCFL rad2);

/// determine whether point x, y is within circle
bool ARC_CollisionCircleXY(ARC_Point* pos, ARC_Point* c, ARCFL rad);
// LINE ///////////////////////////////////////////////////////////


/***
 Line Line Collision
	http://www.geometryalgorithms.com/Archive/algorithm_0104/algorithm_0104B.htm#intersect2D_SegSeg()
	intersect2D_2Segments(): the intersection of 2 finite 2D segments
	Input:  two finite segments S1 and S2
	Output: *I0 = intersect point (when it exists)
	Return: 0=disjoint (no intersect)
	1=intersect in unique point I0
	2=overlap in segment from I0 to I1
*/
int ARC_CollisionLineLine(ARC_Point* S1P0, ARC_Point* S1P1, ARC_Point* S2P0, ARC_Point* S2P1, ARC_Point** I0);
//===================================================================

/**
	inSegment(): determine if a point is inside a segment
	Input:  a point P, and a collinear segment S
	Return: true = P is inside S
			false = P is not inside S
*/
bool ARC_CollisionInSegment( ARC_Point* P, ARC_Point* S0, ARC_Point* S1);


// POINT //////////////////////////////////////////////////////////

/// returns true if this point is inside of this polygon
bool ARC_CollisionPolygonXY(ARC_Point* p, ARC_Point* points, int polyLength);

#ifdef __cplusplus
}
#endif

#endif
