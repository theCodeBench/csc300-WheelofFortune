/*************************************************************************//**
 * @file spinButton.h
 *
 * @section depends_on Depends On
 * @verbatim

   must include:

#include "spinButton.h"
#include "graphics.h"
#include <unistd.h>
#include "loadBMP.h"

  *****************************************************************************/
#include "spinButton.h"
#include "graphics.h"
#include <unistd.h>
#include "loadBMP.h"



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function draws the spin button in the correct location.
 *
 * @returns void
 ******************************************************************************/
void spinButton :: drawTile()
{
    DrawSector(s, color);
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function loads in the new BMP using the loadBMP function
 *
 * @returns void
 ******************************************************************************/
void spinButton::loadspinBMP()
{
    int rows = 52, cols = 40;
    chdir("Letters");
    loadBMP(filename, rows, cols, data);
    chdir("..");
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function creates a random amount for the winnings spun by the spin
 * button
 *
 * @returns int returns the amount of money that was generated
 ******************************************************************************/
int spinButton ::amountWon()
{
    int winnings = 0;
    srand(time(NULL));
    winnings = rand() % 12 - 1;
    if (winnings > 0)
        return 100 * winnings;
    return winnings;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function draws the actual spin bmp over the specified location
 *
 * @returns void
 ******************************************************************************/
void spinButton ::drawSpin()
{
    drawTexture(x1, y1, x2, y2, data, width, height);
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     This function sets the initial position of the spin button.
 *
 * @returns void
 ******************************************************************************/
void spinButton :: initposition()
{

    x1 = 600;
    y1 = 100;
    x2 = x1 + 54;
    y2 = y1 - 52;

}



/***************************************************************************//**
 * @author Jeremy
 *
 *
 * @par Description
 *     This function checks if the spin button has been clicked and returns
 * the state of the button.
 *
 * @param[in] x - the x coordinate of the button
 * @param[in] y - the y coordinate of the button
 *
 * @returns true  returns true if the button is clicked
 * @returns false returns false if the button is not clicked
 ******************************************************************************/
bool spinButton :: clicked(int x, int y)
{
    if (x > x1 && x < x2 )
    {
        if (glutGet(GLUT_WINDOW_HEIGHT) - y < y1 &&
                glutGet(GLUT_WINDOW_HEIGHT) - y > y2)
        {
            return true;
        }
    }
    return false;
}
