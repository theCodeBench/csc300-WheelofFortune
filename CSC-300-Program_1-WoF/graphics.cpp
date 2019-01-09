/*
* @file graphics.cpp
*
*  @subpage graphics.h
 *
 * @section depends_on Depends On
 * @verbatim

   must include:

include files
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

the GLUT header automatically includes gl.h and glu.h
#include <GL/glut.h>
#include "graphics.h"
#include "globals.h"
#include "loadBMP.h"

* @section original_auths Original Authors
 * @verbatim
                    ***** graphics.cpp *****

OpenGL graphics program, illustrating use of GLUT and callback functions.

Author: John M. Weiss, Ph.D.
Class:  CSC300 Data Structures
Date:   Fall 2015

Modifications:

*
*
 * @section course_section Course Information
 *
 * @author Zac and Ryan and Jeremy
 *
 * @date Feb 19, 2016
 *
 * @par Professor:
 *         Paul Hinker
 *
 * @par Course:
 *         CSC300
 *
 * @par Location:
 *         McLaury SDSM&T
 *
 * @section program_section Program Information
 *
 * @details This program
 *
 *
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 * @verbatim
 *
 *      Compile with main.cpp and it's dependancies on Fedora linux distr.
 *      Make sure LIBS = -lGL -lglut -lGLU -lm
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *

 *
 * @par Modifications and Development Timeline:
   @verbatim

Changes as logged by commit notes from GitLab.

   @endverbatim
 *
*/

// include files
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// the GLUT header automatically includes gl.h and glu.h
#include <GL/glut.h>
#include "graphics.h"
#include "globals.h"
#include "loadBMP.h"

typedef unsigned char byte;

/*
#include "line.h"
#include "ellipse.h"
#include "rectangle.h"
*/
/******************************************************************************/
/*                          useful graphics routines                          */
/******************************************************************************/
/***************************************************************************//**
 * @author John M. Weiss, Ph.D.
 *
 *
 * @par Description
 *     This function created by Dr. Weiss
 *
 * @returns void
 ******************************************************************************/
// draw a line using the given RGB color value
void DrawLine( float x1, float y1, float x2, float y2, const float color[] )
{
    // glLineWidth( 10 );
    glColor3fv( color );
    glBegin( GL_LINES );
    glVertex2f( x1, y1 );
    glVertex2f( x2, y2 );
    glEnd();
    glFlush();
}

/******************************************************************************/
/***************************************************************************//**
 * @author John M. Weiss, Ph.D.
 *
 *
 * @par Description
 *     This function created by Dr. Weiss
 *
 * @returns void
 ******************************************************************************/
// draw a rectangle using the given RGB color value
void DrawRectangle( float x1, float y1, float x2, float y2, const float color[] )
{
    glColor3fv( color );
    glBegin( GL_LINE_LOOP );
    glVertex2f( x1, y1 );
    glVertex2f( x2, y1 );
    glVertex2f( x2, y2 );
    glVertex2f( x1, y2 );
    glEnd();
    glFlush();
}

/******************************************************************************/
/***************************************************************************//**
 * @author John M. Weiss, Ph.D.
 *
 *
 * @par Description
 *     This function created by Dr. Weiss
 *
 * @returns void
 ******************************************************************************/
// draw a filled rectangle using the given RGB color value
void DrawFilledRectangle( float x1, float y1, float x2, float y2, const float color[] )
{
    glColor3fv( color );
    glBegin( GL_POLYGON );
    glVertex2f( x1, y1 );
    glVertex2f( x2, y1 );
    glVertex2f( x2, y2 );
    glVertex2f( x1, y2 );
    glEnd();
    glFlush();
}

/******************************************************************************/
/***************************************************************************//**
 * @author John M. Weiss, Ph.D.
 *
 *
 * @par Description
 *     This function created by Dr. Weiss
 *
 * @returns void
 ******************************************************************************/
// draw an ellipse of given radii at a specified position using the given RGB color value
void DrawEllipse( float xRadius, float yRadius, int x, int y, const float color[] )
{
    float radius = xRadius < yRadius ? xRadius : yRadius;   // stretch circle into ellipse
    glColor3fv( color );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( x, y, 0 );
    glScalef( xRadius / radius, yRadius / radius, 1.0 );    // by ratio of major to minor axes
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, radius - 1, radius, int( radius ), 1 );
    gluDeleteQuadric( disk );
    glLoadIdentity();
    glFlush();
}

/******************************************************************************/
/***************************************************************************//**
 * @author John M. Weiss, Ph.D.
 *
 *
 * @par Description
 *     This function created by Dr. Weiss
 *
 * @returns void
 ******************************************************************************/
// draw an ellipse of given radii at a specified position using the given RGB color value
void DrawFilledEllipse( float xRadius, float yRadius, int x, int y, const float color[] )
{
    float radius = xRadius < yRadius ? xRadius : yRadius;   // stretch circle into ellipse
    glColor3fv( color );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( x, y, 0 );
    glScalef( xRadius / radius, yRadius / radius, 1.0 );    // by ratio of major to minor axes
    GLUquadricObj *disk = gluNewQuadric();
    gluDisk( disk, 0, radius, int( radius ), 1 );
    gluDeleteQuadric( disk );
    glLoadIdentity();
    glFlush();
}

/******************************************************************************/
/***************************************************************************//**
 * @author John M. Weiss, Ph.D. and Zac
 *
 *
 * @par Description
 *     DrawTextString modified from Dr. Weiss's origional code.
 *
 * @returns void
 ******************************************************************************/
// write a text string at a specified position using the given RGB color value
void DrawTextString( string text, int x, int y, const float color[] )
{
    glColor3fv(White);
    glRasterPos2i( x, y );
    for (unsigned int i = 0; i < text.length(); i++)
        glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, text[i] );
}
/***************************************************************************//**
 * @author Zac and Ryan and Jeremy
 *
 *
 * @par Description
 *     DrawSector - this overload of DrawSector takes an int s that designates
 * a sector of a screen location and a color array and outputs a tile of that
 * color in that sector.
 *
 * @returns void
 ******************************************************************************/
void DrawSector(int s, const float color[])
{
    float height = glutGet(GLUT_WINDOW_HEIGHT) / 10,
          width = glutGet(GLUT_WINDOW_WIDTH) / 25;

    float x1 = (s % 25) * width,
          y1 = glutGet(GLUT_WINDOW_HEIGHT) - (s / 25) * height,
          x2 = (s % 25) * width + width,
          y2 = glutGet(GLUT_WINDOW_HEIGHT) - (s / 25) * height - height;

    DrawFilledRectangle(x1, y1, x2, y2, color);
    DrawRectangle(x1, y1, x2, y2, Blue);


}
/***************************************************************************//**
 * @author Zac and Ryan and Jeremy
 *
 *
 * @par Description
 *     DrawSector - will fill in a sector of proper size with color.
 * @returns void
 ******************************************************************************/
void drawTexture(float x1, float y1, float x2, float y2, byte* data,
                 float width, float height)
{

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, glutGet(GLUT_WINDOW_WIDTH), 0.0, glutGet(GLUT_WINDOW_HEIGHT), -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();


    glLoadIdentity();
    glDisable(GL_LIGHTING);


    GLuint texture;

    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, texture);

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );


    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(x1, y2);
    glTexCoord2f(0, 1); glVertex2f(x1, y1);
    glTexCoord2f(1, 1); glVertex2f(x2, y1);
    glTexCoord2f(1, 0); glVertex2f(x2, y2);
    glEnd();
    glFlush();
}
/***************************************************************************//**
 * @author Zac and Ryan and Jeremy
 *
 *
 * @par Description
 *     This overload of DrawSector takes a sector and pointer to a byte and 
 * outputs a drawn sector with the texture stored at that byte address.
 *
 * @returns void
 ******************************************************************************/
void DrawSector(int s, byte* data)
{
    int border = 1;
    float height = glutGet(GLUT_WINDOW_HEIGHT) / 10,
          width = glutGet(GLUT_WINDOW_WIDTH) / 25;
    float x1 = (s % 25) * width + border,
          y1 = glutGet(GLUT_WINDOW_HEIGHT) - (s / 25) * height - border,
          x2 = (s % 25) * width + width - border,
          y2 = glutGet(GLUT_WINDOW_HEIGHT) - (s / 25) * height - height + border;

    drawTexture(x1, y1, x2, y2, data, width, height);
    DrawRectangle(x1, y1, x2, y2, Black);
    glFlush();

}
