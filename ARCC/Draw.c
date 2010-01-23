
#include "Draw.h"

void ARC_DrawInit()
{
	drawLog = log4c_category_get("arc.draw");
}

void ARC_DrawSetGLColor(ARC_Color *c)
{
	glColor4ub(c->r, c->g, c->b, c->a);
}

unsigned char ARC_DrawGetColorCell(ARC_Color *c, int index)
{
	switch(index)
	{
		case 0:
			return c->r;
			break;
		case 1:
			return c->g;
			break;
		case 2:
			return c->b;
			break;
		case 3:
			return c->a;
			break;
	}

	log4c_category_log(drawLog, LOG4C_PRIORITY_ERROR, "Bad index for ARC_DrawGetColorCell");
	return 0;
}

void ARC_DrawColorBrighten(ARC_Color *c, int by)
{
	c->r += by;
	c->g += by;
	c->b += by;
}

void ARC_DrawColorDarken(ARC_Color *c, int by)
{
	c->r -= by;
	c->g -= by;
	c->b -= by;
}


/// simply draw image to screen with given image ID from the center with pivot points
void ARC_DrawImage(ARC_Texture* texture, ARC_Point* pos, ARC_Size* size, ARC_Point* pivot, RADIANS angle, ARC_Color* color)
{
	// center calculations
	ARCFL halfWidth = size->w/2;
	ARCFL halfHeight = size->h/2;

	ARCFL texw = (texture->imageSize.w / texture->textureSize.w);
	ARCFL texh = (texture->imageSize.h / texture->textureSize.h);

	// enable 2d textures and bind texture
	glEnable(GL_TEXTURE_2D);

	// bind texture ID to this tex
	glBindTexture(GL_TEXTURE_2D, texture->ID);

	// set color to one given
	ARC_DrawSetGLColor(color);

	glPushMatrix();

	// rotate and translate
	glTranslatef(pos->x,pos->y,0);
	glRotatef(ARC_MathRadiansToDegrees(angle), 0, 0, 1);

	// draw image at given coords, binding texture appropriately
	glBegin(GL_QUADS);

	// -halfWidth and -halfHeight act as ancors to rotate from the center
	glTexCoord2d(0,0); glVertex2f(-halfWidth + pivot->x, -halfHeight + pivot->y);

	glTexCoord2d(0,texh); glVertex2f(	-halfWidth + pivot->x,
									-halfHeight + size->h + pivot->y);

	glTexCoord2d(texw,texh); glVertex2f(	-halfWidth + size->w + pivot->x,
									-halfHeight + size->h + pivot->y);

	glTexCoord2d(texw,0); glVertex2f(	-halfWidth + size->w + pivot->x,
									-halfHeight + pivot->y);

	glEnd();

	glPopMatrix();
}

/// draw image from the top left location
void ARC_DrawImageTopLeft(ARC_Texture* texture, ARC_Point* pos, ARC_Size* size, ARC_Color* color)
{
	// enable 2d textures and bind texture
	glEnable(GL_TEXTURE_2D);

	// bind texture ID to this tex
	glBindTexture(GL_TEXTURE_2D, texture->ID);

	// set color to one given
	ARC_DrawColorSetGL(color);

	glPushMatrix();

	// rotate and translate
	glTranslatef(pos->x,pos->y,0);

	ARCFL texw = texture->imageSize.w / texture->textureSize.w;
	ARCFL texh = texture->imageSize.h / texture->textureSize.h;

	// draw image at given coords, binding texture appropriately
	glBegin(GL_QUADS);

	// -halfWidth and -halfHeight act as ancors to rotate from the center
	glTexCoord2d(0,0); glVertex2f(0 , 0);

	glTexCoord2d(0,texh); glVertex2f(0, size->h);

	glTexCoord2d(texw,texh); glVertex2f(size->w , size->h);

	glTexCoord2d(texw,0); glVertex2f(size->w , 0);

	glEnd();

	glPopMatrix();
}

/// draw a subsection of an image with the top-left at 0,0
void ARC_DrawImageSubsection(ARC_Texture* texture, ARC_Point* topLeft, ARC_Point* rightBottom, ARC_Color* color)
{
	// enable 2d textures and bind texture
	glEnable(GL_TEXTURE_2D);

	// bind texture ID to this tex
	glBindTexture(GL_TEXTURE_2D, texture->ID);

	// set color
	ARC_DrawSetGLColor(color);

	// draw image at given coords, binding texture appropriately
	glBegin(GL_QUADS);

	ARCFL width = texture->textureSize.w;
	ARCFL height = texture->textureSize.h;

	ARCFL
		tLeft = topLeft->x / width,
		tTop = topLeft->y / height,
		tRight = rightBottom->x / width,
		tBottom = rightBottom->y / height;

	glTexCoord2d(tLeft, tTop);
	glVertex2f(0, 0);

	glTexCoord2d(tLeft, tBottom);
	glVertex2f(0, rightBottom->y - topLeft->y);

	glTexCoord2d(tRight, tBottom);
	glVertex2f(rightBottom->x - topLeft->x , rightBottom->y - topLeft->y);

	glTexCoord2d(tRight, tTop);
	glVertex2f(rightBottom->x - topLeft->x , 0);

	glEnd();
}


/// draw pixel at position and color
void ARC_DrawPixel(ARC_Point* pos, ARC_DrawOptions* attr)
{
	// disable gl textures
	glDisable(GL_TEXTURE_2D);

	// set color to one given
	ARC_DrawColorSetGL(attr->fill);

	// make sure the line width is only 1 pixel wide
	glLineWidth(1);

	// draw line
	glBegin(GL_LINE_LOOP);

	glVertex2f(pos->x, pos->y);
	glVertex2f(pos->x+1, pos->y);

	glEnd();
}

/// draw line with color
void ARC_DrawLine( ARC_Point* pos1, ARC_Point* pos2, ARC_DrawOptions* attr )
{
	// disable gl textures
	glDisable(GL_TEXTURE_2D);

	// set color to one given
	ARC_DrawColorSetGL(attr->stroke);

	glEnable(GL_LINE_SMOOTH);

	// draw line
	glBegin(GL_LINES);

	glVertex2f(pos1->x, pos1->y);
	glVertex2f(pos2->x, pos2->y);

	glEnd();
}

/// draw circle at position, size (radius), detail (vertex's), and color
void ARC_DrawCircle(ARC_Point* pos, ARCFL radius, ARC_DrawOptions* attr)
{
	// primitives can only be drawn once textures are disabled
	glDisable(GL_TEXTURE_2D);

	// we will be drawing lines
	if (attr->isFill)
	{
		ARC_DrawColorSetGL(attr->fill);
		glBegin(GL_POLYGON);
	}
	else
	{
		ARC_DrawColorSetGL(attr->stroke);
		glLineWidth(attr->strokeWidth);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINE_LOOP);
	}

	ARCFL px, py;

	for (ARCFL i = 0; i < 360; i+= 360.0/attr->detail)
	{
		// create polar coordinate
		px = radius;
		py = i;

		// translate it to rectangular
		py = degreesToRadians(py); // convert degrees to radian

		ARCFL x_save = px;

		px = x_save * cos(py); // i know, polar->y is used too much, but i'd like to eliminate the need
		py = x_save * sin(py); // for too many variables

		// and draw it
		glVertex2f(pos->x+px, pos->y+py);
	}

	glEnd();
}

/// draw circle at position, size (radius), detail (vertex's), and color
void ARC_DrawEllipse(ARC_Point* pos, ARC_Point* radius, ARC_DrawOptions* attr)
{
	// primitives can only be drawn once textures are disabled
	glDisable(GL_TEXTURE_2D);

	// we will be drawing lines
	if (attr->isFill)
	{
		ARC_DrawColorSetGL(attr->fill);
		glBegin(GL_POLYGON);
	}
	else
	{
		ARC_DrawColorSetGL(attr->stroke);
		glLineWidth(attr->strokeWidth);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINE_LOOP);
	}

	for (ARCFL i = 0; i < 360; i+= 360.0/attr->detail)
	{
		float degInRad = degreesToRadians(i);
		glVertex2f(pos->x+cos(degInRad)*radius->x, pos->y+sin(degInRad)*radius->y);
	}

	glEnd();
}

/// draw rectange with given position, size, and color
void ARC_DrawRectangle(ARC_Point* pos, ARC_Size* size, ARC_DrawOptions* attr)
{
	// disable images
	glDisable(GL_TEXTURE_2D);

	// set color to one given
	ARC_DrawColorSetGL(attr->fill);

	// we will be drawing lines
	if (attr->isFill)
	{
		ARC_DrawColorSetGL(attr->fill);
		glBegin(GL_POLYGON);
	}
	else
	{
		ARC_DrawColorSetGL(attr->stroke);
		glLineWidth(attr->strokeWidth);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINE_LOOP);
	}

	// draw box to the screen
	glVertex2f(pos->x+size->w, pos->y);

	glVertex2f(pos->x+size->w, pos->y+size->h);

	glVertex2f(pos->x, pos->y + size->h);

	glVertex2f(pos->x, pos->y);

	glEnd();
}

/// draw rectange with given position, size, and color
void ARC_DrawRoundEdgeRect(ARC_Point* pos, ARC_Size* size, ARC_DrawOptions* attr)
{
	// disable images
	glDisable(GL_TEXTURE_2D);

	// we will be drawing lines
	if (attr->isFill)
	{
		ARC_DrawColorSetGL(attr->fill);
		glBegin(GL_POLYGON);
	}
	else
	{
		ARC_DrawColorSetGL(attr->stroke);
		glLineWidth(attr->strokeWidth);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINE_LOOP);
	}

	// mult detail by 4
	int detail = attr->detail * 4;

	ARCFL px, py;

	ARC_Point start;
	start.x = pos->x+(size->h/2);
	start.y = pos->y+(size->h/2);

	// first draw from 90-->180
	for (ARCFL i = 90; i <= 270; i += 360.0/detail)
	{
		// create polar coordinate
		px = size->h/2;
		py = i;

		// translate it to rectangular
		py = degreesToRadians(py); // convert degrees to radian

		ARCFL x_save = px;

		px = x_save * cos(py); // i know, polar->y is used too much, but i'd like to eliminate the need
		py = x_save * sin(py); // for too many variables

		// and draw it
		glVertex2f(start.x+px, start.y+py);
	}

	// draw from top left --> right left
	glVertex2f(pos->x+(size->h/2), pos->y);
	glVertex2f(pos->x+size->w-(size->h/2), pos->y);

	start.x = pos->x+size->w-(size->h/2);
	start.y = pos->y+(size->h/2);

	// first draw from 270-->360
	for (ARCFL i = 270; i <= 360; i += 360.0/detail)
	{
		// create polar coordinate
		px = size->h/2;
		py = i;

		// translate it to rectangular
		py = degreesToRadians(py); // convert degrees to radian

		ARCFL x_save = px;

		px = x_save * cos(py); // i know, polar->y is used too much, but i'd like to eliminate the need
		py = x_save * sin(py); // for too many variables

		// and draw it
		glVertex2f(start.x+px, start.y+py);
	}

	// first draw from 270-->360
	for (ARCFL i = 0; i <= 90; i += 360.0/detail)
	{
		// create polar coordinate
		px = size->h/2;
		py = i;

		// translate it to rectangular
		py = degreesToRadians(py); // convert degrees to radian

		ARCFL x_save = px;

		px = x_save * cos(py); // i know, polar->y is used too much, but i'd like to eliminate the need
		py = x_save * sin(py); // for too many variables

		// and draw it
		glVertex2f(start.x+px, start.y+py);
	}

	// next draw top left corner
	glEnd();
}

/// draw polygon
void ARC_DrawPolygon(ARC_Point* pos, ARC_Point* polygon, int polylength, ARC_DrawOptions* attr)
{
	int i;

	// disable images
	glDisable(GL_TEXTURE_2D);

	// we will be drawing lines
	if (attr->isFill)
	{
		ARC_DrawColorSetGL(attr->fill);
		glBegin(GL_POLYGON);
	}
	else
	{
		ARC_DrawColorSetGL(attr->stroke);
		glLineWidth(attr->strokeWidth);
		glEnable(GL_LINE_SMOOTH);
		glBegin(GL_LINE_LOOP);
	}

	for (i = 0; i < polylength; i++)
	{
		glVertex2f(pos->x + polygon[i].x, pos->y + polygon[i].y);
	}

	glEnd();
}

/// draw polygon
void ARC_DrawPolyLine(ARC_Point* pos, ARC_Point* polygon, int polylength, ARC_DrawOptions* attr)
{
	// disable images
	glDisable(GL_TEXTURE_2D);

	ARC_DrawColorSetGL(attr->stroke);
	glLineWidth(attr->strokeWidth);
	glEnable(GL_LINE_SMOOTH);
	glBegin(GL_LINES);

	for (int i = 0; i < polylength; i++)
	{
		glVertex2f(pos->x + polygon[i].x, pos->y + polygon[i].y);
	}

	glEnd();
}
