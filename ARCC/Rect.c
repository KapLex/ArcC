#include "Rect.h"

bool ARC_RectContains(ARC_Rect *r, ARC_Point* p)
{
	return (   p->x >= r->topLeft.x
			&& p->y >= r->topLeft.y
			&& p->x < r->topLeft.x + r->size.w
			&& p->y < r->topLeft.y + r->size.h);
}

/// tests if two rects intersect. both are closed
bool ARC_RectIntersects(ARC_Rect *r1, ARC_Rect *r2)
{
	if(r1->topLeft.x >= r2->topLeft.x + r2->size.w)
		return false;
	if(r1->topLeft.y >= r2->topLeft.y + r2->size.h)
		return false;
	if(r1->topLeft.x + r2->size.w <= r2->topLeft.x)
		return false;
	if(r1->topLeft.y + r2->size.h <= r2->topLeft.y)
		return false;

	return true;
}

