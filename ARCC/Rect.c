#include "Rect.h"

bool ARC_RectContains(ARC_Point* p)
{
	return (p->x >= topLeft->x && p->y >= topLeft->y && p->x < topLeft->x + size->w && p->y < topLeft->y + size->h);
}

/// tests if two rects intersect. both are closed
bool ARC_RectIntersects(Rect* r)
{
	if(r->topLeft->x >= topLeft->x + size->w)
		return false;
	if(r->topLeft->y >= topLeft->y + size->h)
		return false;
	if(r->topLeft->x + r->size->w <= topLeft->x)
		return false;
	if(r->topLeft->y + r->size->h <= topLeft->y)
		return false;

	return true;
}

