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
ARCFL ARC_PointCross(ARC_Point *p, ARC_Point v)
{
	return x * v.y - y * v.x;
}

/** Scalar cross product */
ARC_Point ARC_PointCross(ARC_Point *p, ARCFL s)
{
	Point p;
	p.x = -s * y;
	p.y = s * x;
	return p;
}

/** Vector bDot product */
ARCFL ARC_PointDot(ARC_Point *p, ARC_Point v) {
	return x * v.x + y * v.y;
}

/** Vector bCross product */
ARCFL ARC_PointCross(ARC_Point *p, ARC_Point v) {
	return x * v.y - y * v.x;
}

/** Scalar cross product */
ARC_Point ARC_PointCross(ARC_Point *p, ARCFL s) {
	return Point(-s * y, s * x);
}

/** Scalar addition */
ARC_Point ARC_PointAdd(ARC_Point *p, ARCFL V)
{
	return Point(x + V, y + V);
}

/** Scalar subtraction */
ARC_Point ARC_PointSub(ARC_Point *p, ARCFL n)
{
	return Point(x - n, y - n);
}

/** Scalar addition */
ARC_Point ARC_PointAddAssign(ARC_Point *p, ARCFL V)
{
	x += V;
	y += V;
	return *this;
}

/** Scalar subtraction */
ARC_Point ARC_PointSubAssign(ARC_Point *p, ARCFL V)
{
	x -= V;
	y -= V;
	return *this;
}

/** Scalar multiplication */
ARC_Point ARC_PointMulAssign(ARC_Point *p, ARCFL s)
{
	x *= s;
	y *= s;
	return *this;
}

/** Scalar multiplication */
ARC_Point ARC_PointMul(ARC_Point *p, ARCFL s)
{
	return Point(x * s, y * s);
}

/** 2x2 matrix multiplication */
ARC_Point ARC_PointMul(ARC_Point *p, Matrix a)
{
	return Point(a.col1.x * x + a.col2.x * y, a.col1.y * x + a.col2.y * y);
}

/** Scalar division */
ARC_Point ARC_PointDivAssign(ARC_Point *p, ARCFL s)
{
	x /= s;
	y /= s;
	return *this;
}

/** Scalar division */
ARC_Point ARC_PointDiv(ARC_Point *p, ARCFL s)
{
	return Point(x / s, y / s);
}

/** Vector addition */
ARC_Point ARC_PointAddAssign(ARC_Point *p, ARC_Point Other)
{
	x += Other.x;
	y += Other.y;
	return *this;
}

///
ARC_Point ARC_PointAdd(ARC_Point *p, ARC_Point V)
{
	return Point(x + V.x, y + V.y);
}

///
ARC_Point ARC_PointSubAssign(ARC_Point *p, ARC_Point Other)
{
	x -= Other.x;
	y -= Other.y;
	return *this;
}

///
ARC_Point ARC_PointSub(ARC_Point *p, ARC_Point V)
{
	return Point(x - V.x, y - V.y);
}

/// negation
ARC_Point ARC_PointNeg(ARC_Point *p)
{
	return Point(-x, -y);
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
	return x * x + y * y;
}

/// Get the length of this vector (the norm).
ARCFL ARC_PointLength(ARC_Point *p)
{
	return sqrt(x * x + y * y);
}

/// Convert this vector into a unit vector. Returns the length.
ARCFL ARC_PointNormalize(ARC_Point *p)
{
	ARCFL length = length();
	if (length < ARCFL.epsilon)
	{
		return 0.0f;
	}
	ARCFL invLength = 1.0f / length;
	x *= invLength;
	y *= invLength;

	return length;
}

///
ARC_Point ARC_PointNormalizeCopy(ARC_Point *p)
{
	ARC_Point p = *this;
	p.normalize();
	return p;
}

///
ARCFL ARC_PointDistance(ARC_Point *p, ARC_Point v)
{
	ARC_Point delta = Point(x, y) - v;
	return delta.magnitude();
}

///
ARC_Point ARC_PointPerp(ARC_Point *p)
{
	return Point(-y, x);
}

///
ARC_Point ARC_PointClampMax(ARC_Point *p, ARCFL max)
{
	ARCFL l = magnitude();

	if (l > max)
		*this *= (max / l);
	return Point(x, y);
}

///
ARC_Point ARC_PointInterpEquals(ARC_Point *p, ARCFL blend, ARC_Point v)
{
	x += blend * (v.x - x);
	y += blend * (v.y - y);
	return Point(x, y);
}

///
ARC_Point ARC_PointProjectOnto(ARC_Point *p, ARC_Point v)
{
	ARCFL dp = Point(x, y).bDot(v);
	ARCFL f = dp / (v.x * v.x + v.y * v.y);

	return Point(f * v.x, f * v.y);
}

///
ARCFL ARC_PointAngle(ARC_Point *p, ARC_Point v)
{
	return atan2(Point(x, y).bCross(v), Point(x, y).bDot(v));
}

///
static ARC_Point ARC_PointForAngle(ARC_Point *p, ARCFL a)
{
	return Point(cos(a), sin(a));
}

///
void ARC_PointForAngleEquals(ARC_Point *p, ARCFL a)
{
	this.x = cos(a);
	this.y = sin(a);
}

ARC_Point ARC_PointRotate(ARC_Point *p, ARC_Point v)
{
	return Point(x * v.x - y * v.y, x * v.y + y * v.x);
}

///
ARC_Point ARC_PointRotate(ARC_Point *p, ARCFL angle)
{
	ARCFL cos = cos(angle);
	ARCFL sin = sin(angle);

	return Point((cos * x) - (sin * y), (cos * y) + (sin * x));
}

///
ARC_Point ARC_PointRotateAround(ARCFL angle, ARC_Point point)
{
	ARC_Point d = (Point(x, y) - point).rotate(angle);

	x = point.x + d.x;
	y = point.y + d.y;
	return Point(x, y);
}

///
ARC_Point ARC_PointRotateEquals(ARCFL angle)
{
	ARCFL cos = cos(angle);
	ARCFL sin = sin(angle);
	ARCFL rx = (cos * x) - (sin * y);
	ARCFL ry = (cos * y) + (sin * x);

	x = rx;
	y = ry;
	return Point(x, y);
}

///
bool ARC_PointIsZero(ARC_Point *p)
{
	return p->x == 0 && p->y == 0;
}

ARC_Point ARC_PointRotateLeft90(ARC_Point *p)
{
	return Point(-y, x);
}

ARC_Point ARC_PointRotateRight90(ARC_Point *p)
{
	return Point(y, -x);
}


