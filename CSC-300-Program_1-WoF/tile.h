/***************************************************************************//**
 * @file
 ******************************************************************************/
#ifndef _Tile_H_
#define _Tile_H_

#include <string>
#include "GL/glut.h"

/***************************************************************************//**
 * @class Tile
 *
 * @brief
 *    This class designates an area of the GUI to be interacted
 *    with or displayed
 *
 * @par Description
 *    Holds the data concerning the space of the GUI
 *    This class acts as a virtual class for each of the derived
 *    game object classes, with base functions necessary for most
 *    of the other buttons
 ******************************************************************************/

class Tile
{
protected:
  unsigned int s;             /*!< the specified sector of the tile*/
  float color[3] = {0.0f, 0.0f, 0.0f};       /*!< the color of the tile*/
  float x1, y1, x2, y2;               /*!< the location of the tile*/

public:
  Tile();                     /*!< Tile Default Constructor*/

  virtual ~Tile();                 /*!< Tile Default Destructor*/

  virtual void drawTile() = 0;         /*!< change the color of the tile to draw
    on-screen*/

  virtual void initposition() = 0;     /*!< Set the initial position of the Tile
   Object*/

  virtual bool clicked(int x, int y) = 0;   /*!< Check if the Tile is clicked*/
};

#endif
