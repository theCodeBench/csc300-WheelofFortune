/*************************************************************************//**
 * @file spinButton.h
 *
 * @subpage spinButton.cpp
 *
 * @class spinButton.h <spinButton.h>
 *
 * @section depends_on Depends On
 * @verbatim

   must include:

#include "tile.h"

 *
 * @section course_section Course Information
 *
 * @author Zac Christy
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
 *      Compile with main.cpp and it's dependancies.
 *      Make sure LIBS = -lGL -lglut -lGLU -lm
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *

 *
 * @par Modifications and Development Timeline:
   @verbatim

Format: Change date - notes

Changes
--------------------------------------------------------------------------------

Change Feb 18 - created class, minimal code so no other changes needed

   @endverbatim
 *
 *****************************************************************************/
#ifndef _spinButton_H_
#define _spinButton_H_

#include "tile.h"

class spinButton : public Tile
{

protected:

    std::string filename = "Spin2.bmp";       /*!< contains the filename for the
     buttons image*/

    unsigned char * data;             /*!< char signifying the bitmap uploaded*/

    int width = 54, height = 52;        /*!< the size of the bitmap for the spin
     button*/

    int s = 7 * 25 + 13;           /*!< contains sector number for spin button*/

    int lastwinnings = 0;         /*!< the amount of money a player has won from
     the last spin*/

    float x1, y1, x2, y2;                 /*!< the location of the spin button*/


public:
    spinButton() {}                       /*!< constructor for the spin button*/

    ~spinButton() {}                       /*!< destructor for the spin button*/

    void drawTile();                 /*!< draws the tile in the correct sector*/

    void initposition();             /*!< specifies the position of the button*/

    void loadspinBMP();                    /*!< load a new bmp into the screen*/

    bool clicked(int x, int y);     /*!< checks if the button has been clicked*/

    void drawSpin();                /*!< checks if the button has been clicked*/

    void drawWinnings();            /*!< checks if the button has been clicked*/

    int amountWon();   /*!< the amount of money a player has won from the spin*/
};

#endif
