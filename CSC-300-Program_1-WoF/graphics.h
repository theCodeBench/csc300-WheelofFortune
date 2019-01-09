/***************************************************************************//**
 * @file
 ******************************************************************************/


/*******************************************************************************
 * graphics.h
 *
 * @section depends_on Depends On
 * @verbatim
 must include:

#include <GL/glut.h>
#include <string>

 * @section original_auths Original Authors
 * @verbatim

                    ***** graphics.h *****

OpenGL graphics program, illustrating use of GLUT and callback functions.

Author: John M. Weiss, Ph.D.
Class:  CSC300 Data Structures
Date:   Fall 2015

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
*******************************************************************************/

// useful graphics function prototypes

// guard against multiple inclusions
#ifndef _Graphics_H_
#define _Graphics_H_

#include <GL/glut.h>
#include <string>
///byte - will be used to point to stored location data for bmp textures
typedef unsigned char byte;
///  initOpenGL - list of initializing commands to set up window output
void initOpenGL( void );
/// DrawLine - function to draw a glut line
void DrawLine( float x1, float y1, float x2, float y2, const float color[] );
/// DrawRectangle - function to draw a glut rectangle
void DrawRectangle( float x1, float y1, float x2, float y2,
                    const float color[] );
/// DrawRilledRectangle - function to draw a glut filled rectangle
void DrawFilledRectangle( float x1, float y1, float x2, float y2,
                          const float color[] );
/// DrawEllipse - function to draw a glut ellipse
void DrawEllipse( float xRadius, float yRadius, int x, int y,
                  const float color[] );
/// DrawFilledEllipse - function to draw a glut filled ellipse
void DrawFilledEllipse( float xRadius, float yRadius, int x, int y,
                        const float color[] );
/// DrawTextString - function to draw a text string in glut
void DrawTextString( std::string text, int x, int y, const float color[] );
//DrawSector - will fill in a sector of proper size with color.
void DrawSector(int s, const float color[]);
//will fill a sector with BMP of specified filename
void DrawSector(int s, byte* data);
/// will draw a texture of specific non-sectorized OpenGL object
void drawTexture(float x1, float y1, float x2, float y2, byte* data,
                 float width, float height);

#endif
