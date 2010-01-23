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

/// predefined white color
const static ARC_Color ARC_White = {255,255,255};
/// predefined black color
const static ARC_Color ARC_Black = {0,0,0};
/// predefined red color
const static ARC_Color ARC_Red = {255,0,0};
/// predefined green color
const static ARC_Color ARC_Green = {0,255,0};
/// predefined blue color
const static ARC_Color ARC_Blue = {0,0,255};
/// predefined yellow color
const static ARC_Color ARC_Yellow = {255,255,0};
///
const static ARC_Color ARC_AliceBlue = {240, 248, 255};
///
const static ARC_Color ARC_AntiqueWhite= {250, 235, 215};
///
const static ARC_Color ARC_Aqua = {0, 255, 255};
///
const static ARC_Color ARC_Aquamarine= {127, 255, 212 };
///
const static ARC_Color ARC_Azure= {240, 255, 255};
///
const static ARC_Color ARC_Beige = {245, 245, 220};
///
const static ARC_Color ARC_Blanchedalmond = {255, 235, 205};
///
const static ARC_Color ARC_Blueviolet = {138, 43, 226};
///
const static ARC_Color ARC_Brown = {165, 42, 42};
///
const static ARC_Color ARC_Burlywood = {222, 184, 135};
///
const static ARC_Color ARC_Bisque = {255, 228, 196};
///
const static ARC_Color ARC_Cadetblue = {95, 158, 160};
///
const static ARC_Color ARC_Chartreuse = {127, 255, 0};
///
const static ARC_Color ARC_Chocolate = {210, 105, 30};
///
const static ARC_Color ARC_Coral = {255, 127, 80};
///
const static ARC_Color ARC_Cornflowerblue = {100, 149, 237};
///
const static ARC_Color ARC_Cornsilk = {255, 248, 220};
///
const static ARC_Color ARC_Crimson = {220, 20, 60};
///
const static ARC_Color ARC_Cyan = { 0, 255, 255 };
///
const static ARC_Color ARC_Darkblue = {0, 0, 139};
///
const static ARC_Color ARC_Darkgreen = {0, 100, 0};
///
const static ARC_Color ARC_Darkcyan = {0, 139, 139};
///
const static ARC_Color ARC_Darkgoldenrod = {184, 134, 11};
///
const static ARC_Color ARC_Darkgray = {169, 169, 169};
///
const static ARC_Color ARC_Darkkhaki = {189, 183, 107};
///
const static ARC_Color ARC_Darkmagenta = {139, 0, 139};
///
const static ARC_Color ARC_Darkolivegreen = {85, 107, 47};
///
const static ARC_Color ARC_Darkorange = {255, 140, 0};
///
const static ARC_Color ARC_Darkorchid = {153, 50, 204};
///
const static ARC_Color ARC_Darkred = {139, 0, 0};
///
const static ARC_Color ARC_Darksalmon = {233, 150, 122};
///
const static ARC_Color ARC_Darkseagreen = {143, 188, 143};
///
const static ARC_Color ARC_Darkslateblue = {72, 61, 139};
///
const static ARC_Color ARC_Darkslategray = {47, 79, 79};
///
const static ARC_Color ARC_Darkturquoise = {0, 206, 209};
///
const static ARC_Color ARC_Darkviolet = {148, 0, 211};
///
const static ARC_Color ARC_Deeppink = {255, 20, 147};
///
const static ARC_Color ARC_Deepskyblue = {0, 191, 255};
///
const static ARC_Color ARC_Dimgray = {105, 105, 105};
///
const static ARC_Color ARC_Dodgerblue = {30, 144, 255};
///
const static ARC_Color ARC_Firebrick = {178, 34, 34};
///
const static ARC_Color ARC_Floralwhite = {255, 250, 240};
///
const static ARC_Color ARC_Forestgreen = {34, 139, 34};
///
const static ARC_Color ARC_Fuchsia = {255, 0, 255};
///
const static ARC_Color ARC_Gainsboro = {220, 220, 220};
///
const static ARC_Color ARC_Ghostwhite = {248, 248, 255};
///
const static ARC_Color ARC_Gold = {255, 215, 0};
///
const static ARC_Color ARC_Goldenrod = {218, 165, 32};
///
const static ARC_Color ARC_Gray = {128, 128, 128};
///
const static ARC_Color ARC_Greenyellow = {173, 255, 47};
///
const static ARC_Color ARC_Honeydew = {240, 255, 240};
///
const static ARC_Color ARC_Hotpink = {255, 105, 180};
///
const static ARC_Color ARC_Indianred = {205, 92, 92};
///
const static ARC_Color ARC_Indigo = {75, 0, 130};
///
const static ARC_Color ARC_Ivory = {255, 255, 240};
///
const static ARC_Color ARC_Khaki = {240, 230, 140};
///
const static ARC_Color ARC_Lavender = {230, 230, 250};
///
const static ARC_Color ARC_Lavenderblush = {255, 240, 245};
///
const static ARC_Color ARC_Lawngreen = {124, 252, 0};
///
const static ARC_Color ARC_Lemonchiffon = {255, 250, 205};
///
const static ARC_Color ARC_Lightblue = {173, 216, 230};
///
const static ARC_Color ARC_Lightcoral = {240, 128, 128};
///
const static ARC_Color ARC_Lightcyan = {224, 255, 255};
///
const static ARC_Color ARC_Lightgoldenrodyellow = {250, 250, 210};
///
const static ARC_Color ARC_Lightgray = {211, 211, 211};
///
const static ARC_Color ARC_Lightgreen = {144, 238, 144};
///
const static ARC_Color ARC_Lightpink = {255, 182, 193};
///
const static ARC_Color ARC_Lightsalmon = {255, 160, 122};
///
const static ARC_Color ARC_Lightseagreen = {32, 178, 170};
///
const static ARC_Color ARC_Lightskyblue = {135, 206, 250};
///
const static ARC_Color ARC_Lightslategray = {119, 136, 153};
///
const static ARC_Color ARC_Lightsteelblue = {176, 196, 222};
///
const static ARC_Color ARC_Lightyellow = {255, 255, 224};
///
const static ARC_Color ARC_Lime = {0, 255, 0};
///
const static ARC_Color ARC_Limegreen = { 50, 205, 50};
///
const static ARC_Color ARC_Linen = {250, 240, 230};
///
const static ARC_Color ARC_Magenta = {255, 0, 255};
///
const static ARC_Color ARC_Maroon = {128, 0, 0};
///
const static ARC_Color ARC_Mediumaquamarine = {102, 205, 170};
///
const static ARC_Color ARC_Mediumblue = {0, 0, 205};
///
const static ARC_Color ARC_Mediumorchid = {186, 85, 211};
///
const static ARC_Color ARC_Mediumpurple = {147, 112, 219};
///
const static ARC_Color ARC_Mediumseagreen = {60, 179, 113};
///
const static ARC_Color ARC_Mediumslateblue = {123, 104, 238};
///
const static ARC_Color ARC_Mediumspringgreen = {0, 250, 154};
///
const static ARC_Color ARC_Mediumturquoise = {72, 209, 204};
///
const static ARC_Color ARC_Mediumvioletred = {199, 21, 133};
///
const static ARC_Color ARC_Midnightblue = {25, 25, 112};
///
const static ARC_Color ARC_Mintcream = {245, 255, 250};
///
const static ARC_Color ARC_Mistyrose = {255, 228, 225};
///
const static ARC_Color ARC_Moccasin = {255, 228, 181};
///
const static ARC_Color ARC_Navajowhite = {255, 222, 173};
///
const static ARC_Color ARC_Navy = {0, 0, 128};
///
const static ARC_Color ARC_Oldlace = {253, 245, 230};
///
const static ARC_Color ARC_Olive = {128, 128, 0};
///
const static ARC_Color ARC_Olivedrab = {107, 142, 35};
///
const static ARC_Color ARC_Orange = {255, 165, 0};
///
const static ARC_Color ARC_Orangered = {255, 69, 0};
///
const static ARC_Color ARC_Orchid = {218, 112, 214};
///
const static ARC_Color ARC_Palegoldenrod = {238, 232, 170};
///
const static ARC_Color ARC_Palegreen = {152, 251, 152};
///
const static ARC_Color ARC_Paleturquoise = {175, 238, 238};
///
const static ARC_Color ARC_Palevioletred = {219, 112, 147};
///
const static ARC_Color ARC_Papayawhip = {255, 239, 213};
///
const static ARC_Color ARC_Peachpuff = {255, 218, 185};
///
const static ARC_Color ARC_Peru = {205, 133, 63};
///
const static ARC_Color ARC_Pink = {255, 192, 203};
///
const static ARC_Color ARC_Plum = {221, 160, 221};
///
const static ARC_Color ARC_Powderblue = {176, 224, 230};
///
const static ARC_Color ARC_Purple = {128, 0, 128};
///
const static ARC_Color ARC_Rosybrown  = {188, 143, 143};
///
const static ARC_Color ARC_Royalblue = {65, 105, 225};
///
const static ARC_Color ARC_Saddlebrown = {139, 69, 19};
///
const static ARC_Color ARC_Salmon = {250, 128, 114};
///
const static ARC_Color ARC_Sandybrown = {244, 164, 96};
///
const static ARC_Color ARC_Seagreen = {46, 139, 87};
///
const static ARC_Color ARC_Seashell = {255, 245, 238};
///
const static ARC_Color ARC_Sienna = {160, 82, 45};
///
const static ARC_Color ARC_Silver = {192, 192, 192};
///
const static ARC_Color ARC_Skyblue = {135, 206, 235};
///
const static ARC_Color ARC_Slateblue = {106, 90, 205};
///
const static ARC_Color ARC_Slategray = {112, 128, 144};
///
const static ARC_Color ARC_Snow = {255, 250, 250};
///
const static ARC_Color ARC_Springgreen = {0, 255, 127};
///
const static ARC_Color ARC_Steelblue = { 70, 130, 180};
///
const static ARC_Color ARC_Tan = {210, 180, 140};
///
const static ARC_Color ARC_Teal = {0, 128, 128};
///
const static ARC_Color ARC_Thistle = {216, 191, 216};
///
const static ARC_Color ARC_Tomato = {255, 99, 71};
///
const static ARC_Color ARC_Turquoise = {64, 224, 208};
///
const static ARC_Color ARC_Violet = {238, 130, 238};
///
const static ARC_Color ARC_Wheat = {245, 222, 179};
///
const static ARC_Color ARC_Whitesmoke = {245, 245, 245};
///
const static ARC_Color ARC_Yellowgreen = {154, 205, 50};

// if above doesn't work
typedef struct ARC_Colors
{

} ARC_Colors;

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
