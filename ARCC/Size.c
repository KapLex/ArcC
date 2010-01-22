#include "Size.h"

/// returns largest component
ARCFL ARC_SizeMaxComponent(ARC_Size* s)
{
	if (s->w > s->h)
		return s->w;
	return s->h;
}

/// returns smallest component
ARCFL ARC_SizeMinComponent(ARC_Size* s)
{
	if (s->w < s->h)
		return s->w;
	return s->h;
}

// scalar addition
ARC_Size ARC_SizeAddf(ARC_Size* s, ARCFL V)
{
	ARC_Size sz;
	sz.w = s->w+V;
	sz.h = s->h+V;
	return sz;
}

ARC_Size ARC_SizeSubf(ARC_Size* s, ARCFL V)
{
	ARC_Size sz;
	sz.w = s->w-V;
	sz.h = s->h-V;
	return sz;
}

ARC_Size* ARC_SizeAddAssignf(ARC_Size* s, ARCFL V)
{
	s->w += V;
	s->h += V;
	return s;
}

ARC_Size* ARC_SizeSubAssignf(ARC_Size* s, ARCFL V)
{
	s->w -= V;
	s->h -= V;
	return s;
}

// scalar multiplication
ARC_Size* ARC_SizeMulAssignf(ARC_Size* s, ARCFL by)
{
	s->w *= by;
	s->h *= by;
	return s;
}

ARC_Size ARC_SizeMulf(ARC_Size* s, ARCFL V)
{
	ARC_Size sz;
	sz.w = s->w*V;
	sz.h = s->h*V;
	return sz;
}

ARC_Size* ARC_SizeDivAssignf(ARC_Size* s, ARCFL by)
{
	s->w /= by; s->h /= by;
	return s;
}

ARC_Size ARC_SizeDivf(ARC_Size* s, ARCFL V)
{
	ARC_Size sz;
	sz.w = s->w/V;
	sz.h = s->h/V;
	return sz;
}

// vector addition
ARC_Size* ARC_SizeAddAssign(ARC_Size* s, ARC_Size* Other)
{
	s->w += Other->w;
	s->h += Other->h;
	return Other;
}

ARC_Size ARC_SizeAdd(ARC_Size* s, ARC_Size* V)
{
	ARC_Size sz;
	sz.w = s->w+V->w;
	sz.h = s->h+V->h;
	return sz;
}

ARC_Size* ARC_SizeSubAssign(ARC_Size* s, ARC_Size* Other)
{
	s->w -= Other->w;
	s->h -= Other->h;
	return s;
}

ARC_Size ARC_SizeSub(ARC_Size* s, ARC_Size* V)
{
	ARC_Size sz;
	sz.w = s->w-V->w;
	sz.h = s->h-V->h;
	return sz;
}

/// negation
ARC_Size ARC_SizeNeg(ARC_Size* s)
{
	ARC_Size sz;
	sz.w = -s->w;
	sz.h = -s->h;
	return sz;
}

/// make components positive
ARC_Size ARC_SizeAbs(ARC_Size* s)
{
	ARC_Size sz;
	sz.w = abs(s->w);
	sz.h = abs(s->h);
	return sz;
}

/// clamp a vector to min and max values
ARC_Size* ARC_SizeClamp(ARC_Size* s, ARC_Size* min, ARC_Size* max)
{
	s->w = (s->w < min->w)? min->w : ((s->w > max->w)? max->w : s->w);
	s->h = (s->h < min->h)? min->h : ((s->h > max->h)? max->h : s->h);
	return s;
}

/// random vector size between given ranges
ARC_Size* ARC_SizeRandomise(ARC_Size* s, ARC_Size* wMin, ARC_Size* wMax)
{
	//TODO: this cast(int) looks odd
	s->w = randomRange((int)wMin->w, (int)wMax->w);
	s->h = randomRange((int)wMin->h, (int)wMax->h);
	return s;
}



