#include "Texture.h"
#include "Util.h"

void ARC_TextureInit()
{
	textureLog = log4c_category_get("arc.texture");
	gTextureCount = 0;
}

ARC_Texture* ARC_TextureLoad(char* fileName, ARC_TextureOptions* opts)
{
	// load texture
	ARC_Texture t;
	strcpy(t.fileName, fileName);
	loadTexture(&t, fileName);

	if (!opts->keep)
	{
		SDL_FreeSurface(t.image);
	}

	return &t;
}

void ARC_TextureDestroy(ARC_Texture *t)
{
	glDeleteTextures(1, t->ID);
}

/// Enable texturing
void ARC_TextureEnable(ARC_Texture *t)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, t->ID);
}

// hide loadTexture because using it by itself is not 'resource safe'
// you may end up with the same resource loaded twice
/// load texture based on texture's file name
int loadTexture(ARC_Texture *t, char* texFileName)
{
	if (!fileExists(texFileName))
	{
		log4c_category_log(textureLog, LOG4C_PRIORITY_ERROR, "Texture does not exist!");
		return EXIT_FAILURE;
	}

	// read SDL image
	t->image = IMG_Load(toStringz(texFileName));

	if (t->image == NULL)
	{
		log4c_category_log(textureLog, LOG4C_PRIORITY_ERROR, IMG_GetError());
		return EXIT_FAILURE;
	}

	// store the original width and height
	Uint32 orig_w = t->image->w;
	Uint32 orig_h = t->image->h;

	// calculate nearest power-of-two size
	Uint32 pot_w = nextPowerOfTwo(t->image->w);
	Uint32 pot_h = nextPowerOfTwo(t->image->h);

	// convert image to 32 bit RGBA image of power of two size if needed
	if ( ((t->image->format->BitsPerPixel != 32)) || t->image->w != pot_w || t->image->h != pot_h)
	{
		// create new surface of pot size with 32 bit RGBA ordering
		SDL_Surface* newsurf =	SDL_CreateRGBSurface (SDL_SWSURFACE,
										pot_w, pot_h, 32, 0x000000ff,
										0x0000ff00, 0x00ff0000, 0xff000000);

		// copy old surface data onto the new surface
		SDL_SetAlpha(t->image, 0, 0); // set alpha to off, so we just copy all the information
		SDL_FillRect(newsurf, NULL, 0); // fill with transparencity
		SDL_BlitSurface (t->image, NULL, newsurf, NULL);

		// free old surface memory
		SDL_FreeSurface(t->image);

		// point the old surface data to the new surface
		t->image = newsurf;
	}

	// increase our texture count
	gTextureCount++;

	// Bind the texture to the texture arrays index and init the texture
	glBindTexture(GL_TEXTURE_2D, gTextureCount);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	// Build Mipmaps (builds different versions of the picture for distances - looks better)
	gluBuild2DMipmaps(	GL_TEXTURE_2D, 4, t->image->w, t->image->h,
						GL_RGBA, GL_UNSIGNED_BYTE, t->image->pixels);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	log4c_category_log(textureLog, LOG4C_PRIORITY_INFO, "Texture has been loaded");

	// set texture size and ID attributes
	t->textureSize.w = pot_w;
	t->textureSize.h = pot_h;

	t->imageSize.w = orig_w;
	t->imageSize.h = orig_h;

	t->ID = gTextureCount;
}


