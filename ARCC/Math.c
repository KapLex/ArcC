
#include "Math.h"

void ARC_MathInit()
{
	srand ( time(NULL) );
}

/// converts an angle in DEGREES to RADIANS
RADIANS ARC_MathDegreesToRadians(DEGREES deg)
{
	return deg * DEGREE_TO_RADIAN;
}

/// converts an angle in RADIANS to DEGREES
DEGREES ARC_MathRadiansToDegrees(RADIANS rad)
{
	return rad * RADIAN_TO_DEGREE;
}

/// restricts an angle to the 0 - 360 range
DEGREES ARC_MathRestrictDegree(DEGREES deg)
{
	return (int)deg % 360;
}

/// restricts an angle to the 0 - 2PI range
RADIANS ARC_MathRestrictRadian(RADIANS rad)
{
	return (int)rad % (int)TWOPI;
}

/*******************************************************************************

   See if number is in range of target, rangle is variable, use with caution

*******************************************************************************/
bool ARC_MathWithinRange(ARCFL argNum, ARCFL argTarget, ARCFL argRange)
{
	if (argNum <= (argTarget+argRange) && argNum >= (argTarget-argRange))
		return true;

	return false;
}

/*******************************************************************************

   Calculate the distance between 2 points

*******************************************************************************/
ARCFL ARC_MathDistance(ARC_Point *p1, ARC_Point *p2)
{
	return sqrt(pow(p2->x-p1->x, 2) + pow(p2->y-p1->y, 2));
}

/*******************************************************************************

   Returns the next power of two

*******************************************************************************/
int ARC_MathNextPowerOfTwo(int a)
{
	int rval=1;
	while(rval<a) rval<<=1;
	return rval;
}

/*******************************************************************************

   Returns a random integer between a and b

*******************************************************************************/
int ARC_MathRandomRange(ARCFL a, ARCFL b)
{
	return (int)(a + (rand()  % (int)(b+1-a)));
}

/// Finds the roots
bool ARC_MathFindRoots(ARCFL a, ARCFL b, ARCFL c, ARCFL* t0, ARCFL* t1)
{
	/*
	ARCFL d = b*b - (4.0f * a * c);

	if (d < 0.0f)
		return false;

	d = (ARCFL) sqrt(d);

	ARCFL one_over_two_a = 1.0f / (2.0f * a);

	t0 = ((-b - d) * one_over_two_a);
	t1 = ((-b + d) * one_over_two_a);

	if (t1 < t0)
	{
		ARCFL t = t0;
		t0 = t1;
		t1 = t;
	}
	*/
	return true;
}


/// area of a polygon
ARCFL ARC_MathArea(ARC_Point* contour, int n)
{
	ARCFL A=0.0f;

	for(int p=n-1,q=0; q<n; p=q++)
	{
		A+= contour[p].x*contour[q].y - contour[q].x*contour[p].y;
	}

	return A*0.5f;
}

/// Max distance of a given point from a given set of points
ARCFL ARC_MathMaxDistance(ARC_Point* given, ARC_Point* set, int setLength)
{
	ARCFL max = 0;
	ARCFL tmp = 0;

	for (int i = 0; i < setLength; i++)
	{
		// measure distance
		tmp = ARC_MathDistance(given, &set[i]);

		// if greater than current max point, then make this distance the maximum
		if (tmp > max)
			max = tmp;
	}

	return max;
}

/// swap ARCFL values
void ARC_MathSwapf(ARCFL* a, ARCFL* b)
{
	ARCFL *c = a;
	a = b;
	b = c;
}

/// clamp ARCFL value to min and max
ARCFL ARC_MathClampf(ARCFL x, ARCFL min, ARCFL max)
{
	return (x < min)? min : (x > max)? max : x;
}

/// wrap ARCFL value around min and max
ARCFL ARC_MathWrapf(ARCFL x, ARCFL min, ARCFL max)
{
	return (x < min)? (x - min) + max : (x > max)? (x - max) + min : x;
}

/// return sign of a number
ARCFL ARC_MathSignf(ARCFL x)
{
	return x < 0.0f ? -1.0f : 1.0f;
}

/// Random number in range [-1,1]
ARCFL ARC_MathRandom()
{
	ARCFL r = rand();

	r = 2.0f * r - 1.0f;
	return r;
}


