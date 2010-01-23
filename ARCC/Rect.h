/**
    \file Rect.h
    \brief

    Rectangle structure and functions
*/
#ifndef ARC_TYPES_H_
#define ARC_TYPES_H_

#include <stdbool.h>

#include "Point.h"
#include "Size.h"

#ifdef __cplusplus
extern "C" {
#endif

/// Rectangle Structure
typedef struct ARC_Rect
{
	ARC_Point topLeft;
	ARC_Size size;
} ARC_Rect;

/// tests if point is inside rect
bool ARC_RectContains(ARC_Rect *r, ARC_Point* p);

/// tests if two rects intersect. both are closed
bool ARC_RectIntersects(ARC_Rect *r1, ARC_Rect* r2);

#ifdef __cplusplus
}
#endif

#endif
