/*************************************************************************//**
 * @file gameboard.cpp
 *
 * @section depends_on Depends On
 * @verbatim

   must include:

#include "gameboard.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "graphics.h"
#include "game.h"
#include "tile.h"
#include "loadBMP.h"
#include "globals.h"

  *****************************************************************************/
#include "gameboard.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "graphics.h"
#include "game.h"
#include "tile.h"
#include "loadBMP.h"
#include "globals.h"

using namespace std;

#include <GL/glut.h>



/***************************************************************************//**
 * @author Ryan Hinrichs
 *
 *
 * @par Description
 *     Creates the 
 *
 * @param[in] message - takes in the message to be displayed 
 *
 * @returns void
 ******************************************************************************/
void gameboard :: display_message(string message)
{
    const float color[3] = {0.0f, 0.0f, 0.0f};

    DrawTextString( message, 200, glutGet(GLUT_WINDOW_HEIGHT) - 50, color);
}



/***************************************************************************//**
 * @author Zac & Ryan Hinrichs
 *
 *
 * @par Description
 *     Function creates the board with appropriate number of rows and columns 
 * using the DrawScctor function and a variety of bitmaps.
 *
 * @returns void
 ******************************************************************************/
void gameboard :: make_board()
{
    const float color[3] = {0.0f, 0.0f, 0.0f};
    string Hint = "Hint: ";
    int i;


    //drawing first line
    for (i = 0; i < 12; i ++)
    {
        if (guessed[0][i] || display[0][i] == '~')
            DrawSector(52 + i, data[0][i]);
        else
            DrawSector(52 + i, unguessed);
    }

    //drawing second line
    for (i = 0; i < 12; i++)
    {
        if (guessed[1][i] || display[1][i] == '~')
            DrawSector(77 + i, data[1][i]);
        else
            DrawSector(77 + i, unguessed);
    }


	//drawing the third line
    for (i = 0; i < 12; i++)
    {
        if (guessed[2][i] || display[2][i] == '~')
            DrawSector(102 + i, data[2][i]);
        else
            DrawSector(102 + i, unguessed);
    }


	//drawing the fourth line
    for (i = 0; i < 12; i++)
    {
        if (guessed[3][i] || display[3][i] == '~')
            DrawSector(127 + i, data[3][i]);
        else
            DrawSector(127 + i, unguessed);
    }

	///Draws the extra tiles on the ends
    DrawSector(76, blank);
    DrawSector(89, blank);
    DrawSector(101, blank);
    DrawSector(114, blank);

	//Adds a white sector to set the base color for the text
    DrawSector(-1, unguessed);
    Hint = (Hint + hint);
    DrawTextString( Hint, 200, glutGet(GLUT_WINDOW_HEIGHT) - 100, color);
}



/***************************************************************************//**
 * @author Ryan Hinrichs
 *
 *
 * @par Description
 *     This function draws an individual square of the gameboard if bitmaps 
 * aren't available.
 *
 * @param[in] x1 - first x-coordinate of the tile
 * @param[in] y1 - first y-coordinate of the tile
 * @param[in] x2 - second x-coordinate of the tile
 * @param[in] y2 - second y-coordinate of the tile
 * @param[in] color - the color of the tile drawn
 *
 * @returns void
 ******************************************************************************/
void gameboard :: draw(float x1, float y1, float x2, float y2, const float color[])
{

    glColor3fv(White);
    glBegin( GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

    glFlush();
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     Inserts a letter into the gameboard.
 *
 * @param[in] letter - letter to be inserted into the gameboard
 *
 * @returns void
 ******************************************************************************/
void gameboard :: insertChar( char letter)
{
    int i = 52;

    const float color[3] = {0.0, 0.0, 0.0};

    if (letter != '~')
        DrawSector(i, color);
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     Load in the required bitmaps for the gameboard
 *
 * @returns void
 ******************************************************************************/
void gameboard :: loadBmps()
{
    chdir("Letters");
    string filename;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 12; j++)
        {
            if (isalpha(display[i][j]))
            {
                filename = "WheelA.bmp";
                filename[5] = display[i][j];
            }
            else
                filename = "WheelBackground.bmp";
            int rows = 54, cols = 40;
            loadBMP(filename, rows, cols, data[i][j]);
        }
    }
    int rows = 54, cols = 40;
    loadBMP("WheelBackground.bmp", rows, cols, blank);
    rows = 54, cols = 40;
    loadBMP("Wheel~.bmp", rows, cols, unguessed);
    chdir("..");

}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     Outputs the display for debugging
 *
 *
 * @returns void
 ******************************************************************************/
void gameboard :: outputDisplay()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 12; j++)
            cout << display[i][j];
        cout << endl;
    }
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     Sets the puzzle to be the string given to the function
 *
 * @param[in] puzzle - the string signifying the puzzle
 *
 * @returns void
 ******************************************************************************/
void gameboard :: setpuzzle(string puzzle)
{
    answer = puzzle;
    int numlines = 0, currline = 0, linelen[4] = {0};
    unsigned int linespace = 12, line = 0; // line to write to
    string word = "";

    getdim(numlines, linelen);

    if (numlines <= 3)
        line = 1;

	//Sets the puzzle based on spaces and letters
    for (unsigned int i = 0; i < answer.length(); i++)
    {
        if (isalpha(answer[i]))
        {
            word = word + answer[i];
        }
        if (answer[i] == ' ' || i == answer.length() - 1)
        {
            if (word[word.length() - 1] == ' ')
                word.pop_back();

            int offset = (12 - linelen[currline]) / 2;


            if (linespace > word.length())
            {

                for (unsigned int j = 0; j < word.length(); j++)
                    display[line][(12 - linespace) + j + offset] = word[j];

                linespace -= word.length();
            }
            else
            {
                line++;
                currline++;
                if (line > 3)
                    break;
                linespace = 12;
                offset = (12 - linelen[currline]) / 2;
                for (unsigned int j = 0; j < word.length(); j++)
                    display[line][(12 - linespace) + j + offset] = word[j];

                linespace -= word.length();
            }
            word.clear();
            if (linespace > 0)
            {
                display[line][12 - linespace + offset] = '~';
                linespace --;
            }
        }
        if (line > 3)
            canfit = false;
    }

    if (line > 3) //returning false if the puzzle wont fit
        canfit = false;
}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     This is the routine which will validate command line params
 *
 * @param[in] guess - the letter guessed by the user
 * @param[in, out] occurence - the number of occurences of the letter guessed
 *
 * @returns true Guess was found in the puzzle
 * @returns false Guess wasn't found in the puzzle
 ******************************************************************************/
bool gameboard :: checkguess(char guess, int &occurrence)
{
    occurrence = 0;
    guess = toupper(guess);
    if (!isalpha(guess))
        return false;

    bool found = false;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (display[i][j] == guess)
            {
                found = true;
                guessed[i][j] = true;
                occurrence++;
            }
        }
    }
    return found;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     Sets the puzzle to display completely if it is solved
 *
 *
 * @returns true Puzzle is solved
 * @returns false Puzzle is not solved
 ******************************************************************************/
bool gameboard :: puzzle_solved()
{
    bool solved = true;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if (guessed[i][j] == false && display[i][j] != '~')
                solved = false;
        }
    }
    return solved;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     Checks if the string guess was the correct answer
 *
 * @param[in] guess - the string that was the guess given by the user
 *
 * @returns true The guess was correct
 * @returns false The guess was incorrect
 ******************************************************************************/
bool gameboard :: puzzle_solved(string guess)
{
    if (guess == answer)
        return true;
    else
        return false;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     Creates a new hint for a puzzle when the game is reset
 *
 * @param[in] newhint - sets a new hint for the puzzle
 *
 * @returns void
 ******************************************************************************/
void gameboard :: set_hint(string newhint)
{
    hint = newhint;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     Sets the entire puzzle to solved
 *
 *
 * @returns true Tells program that puzzle was solved
 ******************************************************************************/
bool gameboard :: set_puzzle_solved()
{
    bool solved = true;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            guessed[i][j] = true;
        }
    }
    return solved;
}



/***************************************************************************//**
 * @author Zac
 *
 *
 * @par Description
 *     Resets the board in preparation for a new game
 *
 *
 * @returns void
 ******************************************************************************/
void gameboard :: resetboard()
{
    canfit = true;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            display[i][j] = '~';
            data[i][j] = blank;
            guessed[i][j] = false;
        }
    }

}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     Finds the dimensions of the puzzle to be displayed on the gameboard
 *
 * @param[in,out] numlines - The number of lines necessary for the gameboard
 * @param[in] linelen - The length of each of the lines
 *
 * @returns void
 ******************************************************************************/
void gameboard :: getdim(int &numlines, int linelen[])
{
    string word = "";
    unsigned int line = 0;
    unsigned int linespace = 12;
    for (unsigned int i = 0; i < answer.length(); i++)
    {
        if (isalpha(answer[i]))
        {
            word = word + answer[i];
        }
        if (answer[i] == ' ' || i == answer.length() - 1)
        {
            if (word[word.length() - 1] == ' ')
                word.pop_back();
            if (linespace > word.length())
            {

                linespace -= word.length();
            }
            else
            {
                linelen[line] = 11 - linespace;
                linespace = 12;
                line++;
                numlines += 1;
                linespace -= word.length();
            }
            word.clear();
            if (linespace > 0)
            {
                linespace --;
            }
        }
    }
    numlines += 1;
    linelen[line] = 11 - linespace;
}



/***************************************************************************//**
 * @author Jeremy Gamet
 *
 *
 * @par Description
 *     Checks if the puzzle will fit into the gameboard
 *
 * @returns true The puzzle can fit into the gameboard
 * @returns false The puzzle can't fit into the gameboard
 ******************************************************************************/
bool gameboard :: get_canfit()
{
    return canfit;
}

