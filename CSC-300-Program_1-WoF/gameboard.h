/*************************************************************************//**
 * @file gameboard.h
 *
 * @subpage gameboard.cpp
 *
 * @class Gameboard.h <gameboard.h>
 *
 * @section depends_on Depends On
 * @verbatim

   must include:

#include <string>
#include <iostream>

 *
 * @section course_section Course Information
 *
 * @author Zac Christy and Ryan Hinrichs
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

Change Feb 4 - added the main argument testing, and slection loop

Change Feb 4 - added initial board creation

Change Feb 7 - Changed board creation to sector style

Change Feb 19 - completed documentation and formated as a class

   @endverbatim
 *
 *****************************************************************************/
#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <string>
#include <iostream>

using namespace std;
typedef unsigned char byte;

class gameboard {
    string answer;					   /*!< Contains the answer to the puzzle*/
    
    string hint;						 /*!< Contains the hint to the puzzle*/
    
    char display[4][12];								/*!< The display size*/
    
    bool isletter[4][12];			 /*!< Array for checking if it's a letter*/
    
    bool guessed[4][12];			  /*!< Array for checking if it's guessed*/
    
    byte * data[4][12];							   /*!< Data byte for bitmaps*/
    
    byte * blank;								   /*!< Data byte for bitmaps*/
    
    byte * unguessed;					  /*!< Data byte for unguessed bitmap*/
    
    bool canfit = true;					   /*!< Checks if the puzzle will fit*/

    void getdim(int &numlines, int linelen[]);	 /*!< Get the dimensions of the
     gameboard*/

public:
    gameboard(string puzzle)						 /*!< Default Constructor*/
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                display[i][j] = '~';
                guessed[i][j] = false;
            }
        }
        setpuzzle(puzzle);
    }
    
    ~gameboard()									  /*!< Default Destructor*/
    {

    }

    void display_message(string message);	  /*!< Displays the message for the
     gameboard*/
     
    void make_board();							   /*!< Creates the gameboard*/
    
    void draw(float x1, float y1, float x2, float y2, const float color[]);
    												 /*!< Draws the gameboard*/
    
    void insertChar( char letter); /*!< Insert a character into the gameboard*/
    
    void setguessed(int i);						   /*!< Set a spot to guessed*/
        
    void loadBmps();							/*!< Load the various bitmaps*/
        
    void outputDisplay();				   /*!< Create and draw the gameboard*/
    
    void setpuzzle(string puzzle);   /*!< Choose the puzzle for the gameboard*/
    
    bool checkguess(char guess, int &occurrence);      /*!< Check if the letter
     is in the gameboard*/
     
    bool puzzle_solved();				   /*!< Check if the puzzle is solved*/
    
    bool set_puzzle_solved();					/*!< Set the puzzle to solved*/
    
    bool puzzle_solved(string guess);			 /*!< Try to solve the puzzle*/
    
    void set_hint(string newhint);			 /*!< Set the hint for the puzzle*/
    
    void resetboard();							  /*!< Reset the entire board*/
    
    bool get_canfit();						 /*!< Check if the puzzle can fit*/
};
#endif
