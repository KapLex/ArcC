/**
    \file Texture.h
    \brief

    Texture loading
*/

#ifndef ARC_TEXTURE_H_
#define ARC_TEXTURE_H_

// Std
#include <stdbool.h>
#include <string.h>

// Log4c
#include <log4c.h>

// SDL + GL
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Size.h"
#include "Util.h"
#include "Types.h"
#include "Math.h"

#ifdef __cplusplus
extern "C" {
#endif

log4c_category_t* textureLog;
unsigned long gTextureCount;

typedef struct ARC_Texture
{
	unsigned long ID;
	SDL_Surface *image;
	ARC_Size textureSize;
	ARC_Size imageSize;
	char *fileName;
} ARC_Texture;

typedef struct ARC_TextureOptions
{
	bool keep;
} ARC_TextureOptions;

void ARC_TextureInit(void);

ARC_Texture ARC_TextureLoad(char* fileName, ARC_TextureOptions* opts);

void ARC_TextureDestroy(ARC_Texture *t);

/// Enable texturing
void ARC_TextureEnable(ARC_Texture *t);

#ifdef __cplusplus
}
#endif

#endif
