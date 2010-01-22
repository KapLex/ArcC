/** \file Font.h
    \brief

    TrueType font rendering code
*/

#ifndef _ARC_FONT_H_
#define _ARC_FONT_H_

/* Std */
#include <stdbool.h>
#include <string.h>

#include <ft2build.h>
#include FT_FREETYPE_H

// SDL + GL
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

// log4c
#include <log4c.h>

#include "Types.h"

#ifdef __cplusplus
extern "C" {
#endif

log4c_category_t* fontLog;

typedef struct ARC_Font
{
	float height;			///< Holds the height of the font.
	GLuint textures[128];	///< Holds the texture id's
	GLuint list_base;	///< Holds the first display list id
} ARC_Font;

int ARC_FontInit();

int ARC_FontLoad(ARC_Font *font, char *fname, unsigned int height);

int ARC_FontQuit(ARC_Font *font);

void ARC_FontRender(ARC_Font *f, float x, float y, const char *fmt, ...);


#ifdef __cplusplus
}
#endif


#endif
