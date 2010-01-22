#include "Point.h"

/// rotate
ARC_Point ARC_PointRotateCopy(ARC_Point *p, RADIANS angle)
{
	ARC_Point t;

	t.x = p->x*cos(angle)-p->y*sin(angle);
	t.y = p->x*sin(angle)+p->y*cos(angle);

	return t;
}

///
ARC_Point ARC_PointMakePerpTo(ARC_Point *p)
{
	ARC_Point v;
	v.y = p->x;
	v.x = - p->y;
	return v;
}

/*** unfortunately, making this an opCall makes Point(1,1) ambigious...
Point 'constructor' from polar coordinates
*/
ARC_Point ARC_PointFromPolar(ARC_Point *p, ARCFL length, RADIANS angle)
{
	ARC_Point v;
	v.x = length * cos(angle);
	v.y = length * sin(angle);
	return v;
}


/// scaling product
ARC_Point* ARC_PointScalef(ARC_Point *p, ARCFL by)
{
	p->x *= by;
	p->y *= by;
	return p;
}

ARC_Point* ARC_PointScale(ARC_Point *p, ARC_Point* by)
{
	p->x *= by->x;
	p->y *= by->y;
	return p;
}

/** Vector bDot product */
ARCFL ARC_PointDot(ARC_Point *p, ARC_Point *v)
{
	return p->x * v->x + p->y * v->y;
}

/** Vector bCross product */
ARCFL ARC_PointCross(ARC_Point *p, ARC_Point* v)
{
	return p->x * v->y - p->y * v->x;
}

/** Scalar cross product */
ARC_Point ARC_PointCrossf(ARC_Point *p, ARCFL s)
{
	ARC_Point n;
	n.x = -s * p->y;
	n.y = s * p->x;
	return n;
}

/** Scalar addition */
ARC_Point ARC_PointAddf(ARC_Point *p, ARCFL V)
{
	ARC_Point n;
	n.x = p->x + V;
	n.y = p->y + V;
	return n;
}

/** Scalar subtraction */
ARC_Point ARC_PointSubf(ARC_Point *p, ARCFL n)
{
	ARC_Point np;
	np.x = p->x - n;
	np.y = p->y - n;
	return np;
}

/** Scalar addition */
ARC_Point* ARC_PointAddAssignf(ARC_Point *p, ARCFL V)
{
	p->x += V;
	p->y += V;
	return p;
}

/** Scalar subtraction */
ARC_Point* ARC_PointSubAssignf(ARC_Point *p, ARCFL V)
{
	p->x -= V;
	p->y -= V;
	return p;
}

/** Scalar multiplication */
ARC_Point* ARC_PointMulAssignf(ARC_Point *p, ARCFL s)
{
	p->x *= s;
	p->y *= s;
	return p;
}

/** Scalar multiplication */
ARC_Point ARC_PointMulf(ARC_Point *p, ARCFL s)
{
	ARC_Point n;
	n.x = p->x * s;
	n.y = p->y * s;
	return n;
}

/** Scalar division */
ARC_Point* ARC_PointDivAssignf(ARC_Point *p, ARCFL s)
{
	p->x /= s;
	p->y /= s;
	return p;
}

/** Scalar division */
ARC_Point ARC_PointDiv(ARC_Point *p, ARCFL s)
{
	ARC_Point n;
	n.x = p->x / s;
	n.y = p->y / s;
	return n;
}

/** Vector addition */
ARC_Point* ARC_PointAddAssign(ARC_Point *p, ARC_Point Other)
{
	p->x += Other.x;
	p->y += Other.y;
	return p;
}

///
ARC_Point ARC_PointAdd(ARC_Point *p, ARC_Point V)
{
	ARC_Point np;
	np.x = p->x + V.x;
	np.y = p->y + V.y;
	return np;
}

///
ARC_Point* ARC_PointSubAssign(ARC_Point *p, ARC_Point Other)
{
	p->x -= Other.x;
	p->y -= Other.y;
	return p;
}

///
ARC_Point ARC_PointSub(ARC_Point *p, ARC_Point* V)
{
	ARC_Point np;
	np.x = p->x - V->x;
	np.y = p->y - V->y;
	return np;
}


/// negation
ARC_Point ARC_PointNeg(ARC_Point *p)
{
	ARC_Point np;
	np.x = p->x;
	np.y = p->y;
	return np;
}

///
ARCFL ARC_PointMagnitude(ARC_Point* p)
{
	ARCFL mag = sqrt(p->x * p->x + p->y * p->y);
	return mag;
}

/// Get the length squared. For performance, use this instead of
/// Point.length (if possible).
ARCFL ARC_PointLengthSquared(ARC_Point *p)
{
	return p->x * p->x + p->y * p->y;
}

/// Get the length of this vector (the norm).
ARCFL ARC_PointLength(ARC_Point *p)
{
	return sqrt(p->x * p->x + p->y * p->y);
}

/// Convert this vector into a unit vector. Returns the length.
ARCFL ARC_PointNormalize(ARC_Point *p)
{
	ARCFL length = ARC_PointLength(p);

	ARCFL invLength = 1.0f / length;
	p->x *= invLength;
	p->y *= invLength;

	return length;
}

///
ARC_Point* ARC_PointNormalizeCopy(ARC_Point *p)
{
	ARC_PointNormalize(p);
	return p;
}

///
ARCFL ARC_PointDistance(ARC_Point *p, ARC_Point* v)
{
	ARC_Point delta = ARC_PointSub(p, v);
	return ARC_PointMagnitude(&delta);
}

///
ARC_Point ARC_PointPerp(ARC_Point *p)
{
	ARC_Point np;
	np.x = p->x;
	np.y = -p->y;
	return np;
}

///
ARC_Point* ARC_PointClampMax(ARC_Point *p, ARCFL max)
{
	ARCFL l = magnitude();

	if (l > max)
		ARC_PointMulAssign(p, ARC_PointDivf(l, max));
	return p;
}

///
ARCFL ARC_PointAngle(ARC_Point *p, ARC_Point* v)
{
	ARCFL v1 = ARC_PointCross(p, v);
	ARCFL v2 = ARC_PointDot(p, v);

	return atan2(v1,v2);
}

ARC_Point ARC_PointRotate(ARC_Point *p, ARC_Point* v)
{
	ARC_Point np;
	np.x = p->x * v->x - p->y * v->y;
	np.y = p->x * v->y + p->y * v->x;
	return np;
}

///
ARC_Point ARC_PointRotatef(ARC_Point *p, ARCFL angle)
{
	ARCFL cv = cos(angle);
	ARCFL sv = sin(angle);

	ARC_Point np;
	np.x = (cv * p->x) - (sv * p->y);
	np.y = (cv * p->y) + (sv * p->x);

	return np;
}

///
ARC_Point* ARC_PointRotateAround(ARC_Point *p1, ARC_Point *p2, ARCFL angle)
{
	ARC_Point sub = ARC_PointSub(p2, p1);
	ARC_Point diff = ARC_PointRotatef(&sub, angle);

	p1->x = p2->x + diff.x;
	p1->y = p2->y + diff.y;

	return p1;
}

///
ARC_Point ARC_PointRotateEquals(ARC_Point *p, ARCFL angle)
{
	ARCFL cv = cos(angle);
	ARCFL sv = sin(angle);
	ARCFL rx = (cv * p->x) - (sv * p->y);
	ARCFL ry = (cv * p->y) + (sv * p->x);

	ARC_Point np;
	np.x = rx;
	np.y = ry;

	return np;
}

///
bool ARC_PointIsZero(ARC_Point *p)
{
	return p->x == 0 && p->y == 0;
}

ARC_Point ARC_PointRotateLeft90(ARC_Point *p)
{
	ARC_Point np;
	np.x = p->x;
	np.y = -p->y;
	return np;
}

ARC_Point ARC_PointRotateRight90(ARC_Point *p)
{
	ARC_Point np;
	np.x = -p->x;
	np.y = p->y;
	return np; }


