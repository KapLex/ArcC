/**
    \file Size.h
    \brief

    Size structure and functions
*/

#ifndef _ARC_SIZE_H_
#define _ARC_SIZE_H_

#include "Types.h"
#include "Math.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ARC_Size
{
	ARCFL w, h;
} ARC_Size;

/// returns largest component
ARCFL ARC_SizeMaxComponent(ARC_Size* s);

/// returns smallest component
ARCFL ARC_SizeMinComponent(ARC_Size* s);

// scalar addition
ARC_Size* ARC_SizeAddf(ARC_Size* s, ARCFL V);

ARC_Size* ARC_SizeSubf(ARC_Size* s, ARCFL V);

ARC_Size* ARC_SizeAddAssignf(ARC_Size* s, ARCFL V);

ARC_Size* ARC_SizeSubAssignf(ARC_Size* s, ARCFL V);

// scalar multiplication
ARC_Size* ARC_SizeMulAssignf(ARC_Size* s, ARCFL by);

ARC_Size* ARC_SizeMulf(ARC_Size* s, ARCFL by);

ARC_Size* ARC_SizeDivAssignf(ARC_Size* s, ARCFL by);

ARC_Size* ARC_SizeDivf(ARC_Size* s, ARCFL by);

// vector addition
ARC_Size* ARC_SizeAddAssign(ARC_Size* s, ARC_Size* Other);

ARC_Size* ARC_SizeAdd(ARC_Size* s, ARC_Size* V);

ARC_Size* ARC_SizeSubAssign(ARC_Size* s, ARC_Size* Other);

ARC_Size* ARC_SizeSub(ARC_Size* s, ARC_Size* V);

/// negation
ARC_Size* ARC_SizeNeg(ARC_Size* s);

/// make components positive
ARC_Size* ARC_SizeSetAbs(ARC_Size* s);

/// clamp a vector to min and max values
ARC_Size* ARC_SizeClamp(ARC_Size* s, ARC_Size* min, ARC_Size* max);

/// random vector size between given ranges
ARC_Size* ARC_SizeRandomise(ARC_Size* s, ARC_Size* wMin, ARC_Size* wMax);

#ifdef __cplusplus
}
#endif

#endif
