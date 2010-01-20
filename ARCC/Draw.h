/**
    \file Draw.h
    \brief

    Code handling drawing of shapes and images
*/

#ifndef _ARC_DRAW_H_
#define _ARC_DRAW_H_

// Log4c
#include <log4c.h>

#include "Types.h"
#include "Point.h"
#include "Size.h"
#include "Texture.h"

#ifdef __cplusplus
extern "C" {
#endif

log4c_category_t* drawLog;

typedef struct ARC_Color
{
	unsigned char r, g, b, a;
} ARC_Color;

typedef struct ARC_DrawOptions
{
	// Color of shape outline
	ARC_Color* stroke;

	// Color of shape
	ARC_Color* fill;

	// Width of outline, 0 and outline will be ignored
	float strokeWidth;

	// whether or not to fill, otherwise will stroke
	bool isFill;

	// detail to draw curves with
	int detail;
} ARC_DrawOptions;

void ARC_DrawInit();

void ARC_DrawSetGLColor(ARC_Color*c);

unsigned char ARC_DrawGetColorCell(ARC_Color*c, int index);

void ARC_DrawColorBrighten(ARC_Color*c, int by);

void ARC_DrawColorDarken(ARC_Color*c, int by);

/// simply draw image to screen with given image ID from the center with pivot points
void ARC_DrawImage(ARC_Texture* texture, ARC_Point* pos, ARC_Size* size, ARC_Point* pivot, RADIANS angle, ARC_Color* color);

/// draw image from the top left location
void ARC_DrawImageTopLeft(ARC_Texture* texture, ARC_Point* pos, ARC_Size* size, ARC_Color* color);

/// draw a subsection of an image with the top-left at 0,0
void ARC_DrawImageSubsection(ARC_Texture* texture, ARC_Point* topLeft, ARC_Point* rightBottom, ARC_Color* color);

/// draw pixel at position and color
void ARC_DrawPixel(ARC_Point* pos, ARC_DrawOptions* attr);

/// draw line with color
void ARC_DrawLine( ARC_Point* pos1, ARC_Point* pos2, ARC_DrawOptions* attr );

/// draw circle at position, size (radius), detail (vertex's), and color
void ARC_DrawCircle(ARC_Point* pos, ARCFL radius, ARC_DrawOptions* attr);

/// draw circle at position, size (radius), detail (vertex's), and color
void ARC_DrawEllipse(ARC_Point* pos, ARC_Point* radius, ARC_DrawOptions* attr);

/// draw rectange with given position, size, and color
void ARC_DrawRectangle(ARC_Point* pos, ARC_Size* size, ARC_DrawOptions* attr);

/// draw rectange with given position, size, and color
void ARC_DrawRoundEdgeRect(ARC_Point* pos, ARC_Size* size, ARC_DrawOptions* attr);

/// draw polygon
void ARC_DrawPolygon(ARC_Point* pos, ARC_Point* polygon, int polylength, ARC_DrawOptions* attr);

/// draw polygon
void ARC_DrawPolyLine(ARC_Point* pos, ARC_Point* polygon, int polylength, ARC_DrawOptions* attr);

#ifdef __cplusplus
}
#endif

#endif
