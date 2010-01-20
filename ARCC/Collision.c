
#include "Collision.h"

/// whether 2 boxes collide with each other
bool ARC_CollisionBoxBox(ARC_Point* pos1, ARC_Size* size1, ARC_Point* pos2, ARC_Size* size2)
{
	// box's within x range
	if (( pos1->x > pos2->x ||  pos1->x + size1->w > pos2->x) && ( pos1->x < pos2->x + size2->w))
		// box's within y range
		if (( pos1->y > pos2->y ||  pos1->y + size1->h > pos2->y) && ( pos1->y < pos2->y + size2->h))
			return true;

	return false;
}

/// whether a box and circle collide with each other
bool ARC_CollisionBoxCircle(ARC_Point* boxPos, ARC_Size* boxSize, ARC_Point* circlePos, ARCFL radius)
{
	// first we do a simple test to see if center of circle is inside of box
	if (ARC_CollisionBoxXY(circlePos, boxPos, boxSize))
		return true;

	// this next algoritm will determine the distance from given edge
	// of rectangle to the circle->
	// draw line from radframe (x,y) to gx, gy for a better
	// understanding of what this algorithm does

	// destination x and y values this algorithms calculates
	ARCFL gx = 0, gy = 0;

	// box center point
	ARCFL x2 = boxPos->x + boxSize->w/2;
	ARCFL y2 = boxPos->y + boxSize->h/2;

	// box bottom right corner
	ARCFL nw2 = boxPos->x + boxSize->w;
	ARCFL nh2 = boxPos->y + boxSize->h;

	// box frame is above radius frame
	if (y2 <= circlePos->y)
	{
		// middle
		if (circlePos->x >= boxPos->x && circlePos->x <= nw2)
		{
			gx = circlePos->x;
			gy = nh2;
			//debug writefln("top middle");
		}
		// left
		if (circlePos->x > nw2)
		{
			gx = nw2;
			gy = nh2;
			//debug writefln("top left");
		}
		// right
		if (circlePos->x < boxPos->x)
		{
			gx = boxPos->x;
			gy = nh2;
			//debug writefln("top right");
		}
	}
	// box frame below radius frame
	else if (y2 > circlePos->y)
	{
		// middle
		if (circlePos->x >= boxPos->x && circlePos->x <= nw2)
		{
			gx = circlePos->x;
			gy = boxPos->y;
			//debug writefln("bottom middle");
		}
		// left
		if (circlePos->x > nw2)
		{
			gx = nw2;
			gy = boxPos->y;
			//debug writefln("bottom left");
		}
		// right
		if (circlePos->x < boxPos->x)
		{
			gx = boxPos->x;
			gy = boxPos->y;
			//debug writefln("bottom right");
		}
	}

	// boxframe is on right middle of radframe
	if (circlePos->x < x2 && nh2 > circlePos->y && boxPos->y < circlePos->y)
	{
		gx = boxPos->x;
		gy = circlePos->y;
		//debug writefln("right middle");
	}
	// boxframe is on left middle of radframe
	else if (circlePos->x > x2 && nh2 > circlePos->y && boxPos->y < circlePos->y)
	{
		gx = nw2;
		gy = circlePos->y;
		//debug writefln("left middle");
	}

	if (ARC_MathDistance(circlePos->x, circlePos->y, gx, gy) <= radius)
		return true;

	return false;
}

/// determine whether x and y are within given box
bool ARC_CollisionBoxXY(ARC_Point* point, ARC_Point* boxPos, ARC_Size* boxSize)
{
	if (point->x > boxPos->x && point->x < boxPos->x + boxSize->w)
		if (point->y > boxPos->y && point->y < boxPos->y + boxSize->h)
			return true;

    return false;
}

// CIRCLES ///////////////////////////////////////////////////////////

/// determines whether or not 2 circles have collided
bool ARC_CollisionCircleCircle(	ARC_Point* c1, ARCFL rad1, ARC_Point* c2, ARCFL rad2)
{
	if (ARC_MathDistance(c1->x, c1->y, c2->x, c2->y) <= (rad1 + rad2))
		return true;

	return false;
}

/// determine whether point x, y is within circle
bool ARC_CollisionCircleXY(ARC_Point* pos, ARC_Point* c, ARCFL rad)
{
	if (ARC_MathDistance(c->x, c->y, pos->x, pos->y) <= rad)
		return true;

	return false;
}

// LINE ///////////////////////////////////////////////////////////


/***
 Line Line Collision
	http://www->geometryalgorithms->com/Archive/algorithm_0104/algorithm_0104B->htm#intersect2D_SegSeg()
	intersect2D_2Segments(): the intersection of 2 finite 2D segments
	Input:  two finite segments S1 and S2
	Output: *I0 = intersect point (when it exists)
	Return: 0=disjoint (no intersect)
	1=intersect in unique point I0
	2=overlap in segment from I0 to I1
*/
int ARC_CollisionLineLine(ARC_Point* S1P0, ARC_Point* S1P1, ARC_Point* S2P0, ARC_Point* S2P1, ARC_Point** I0)
{
	return ARC_SUCCESS;
}
//===================================================================

/**
	inSegment(): determine if a point is inside a segment
	Input:  a point P, and a collinear segment S
	Return: true = P is inside S
			false = P is not inside S
*/
bool ARC_CollisionInSegment( ARC_Point* P, ARC_Point* S0, ARC_Point* S1)
{
	if (S0->x != S1->x)
	{    // S is not vertical
		if (S0->x <= P->x && P->x <= S1->x)
			return true;
		if (S0->x >= P->x && P->x >= S1->x)
			return true;
	}
	else
	{    // S is vertical, so test y coordinate
		if (S0->y <= P->y && P->y <= S1->y)
			return true;
		if (S0->y >= P->y && P->y >= S1->y)
			return true;
	}
	return false;
}



// POINT //////////////////////////////////////////////////////////

/// returns true if this point is inside of this polygon
bool ARC_CollisionPolygonXY(ARC_Point* p, ARC_Point* points, int polyLength)
{
	bool c = false;
	int i, j;

	for (i = 0, j = polyLength-1; i < polyLength; j = i++)
	{
		if ((((points[i].y <= p->y) && (p->y < points[j].y)) ||
			((points[j].y <= p->y) && (p->y < points[i].y))) &&
			(p->x < (points[j].x - points[i].x) * (p->y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
		{
		  c = !c;
		}
	}

	return c;
}


