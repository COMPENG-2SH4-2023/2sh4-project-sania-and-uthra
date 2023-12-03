#include "GameMechs.h"
#include "MacUILib.h"

// Defualt constructor
GameMechs::GameMechs()
{
    input = 0; 
    boardSizeX = 30;
    boardSizeY = 15; 
    exitFlag = false;
    loseFlag = false;
    score = 0; 
}

// Customizable constructor 
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    boardSizeX = boardX;
    boardSizeY = boardY; 
    exitFlag = false;
    loseFlag = false;
    score = 0;

}

// do you need a destructor? - No

// getter for exit flag
bool GameMechs::getExitFlagStatus()
{
    return exitFlag; 
}

// getter for input
char GameMechs::getInput()
{
     if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input; 
}

// getter for board width 
int GameMechs::getBoardSizeX()
{
    return boardSizeX; 
}

// getter for board height
int GameMechs::getBoardSizeY()
{
    return boardSizeY; 
}

// getter for lose flag 
bool GameMechs::getLoseFlagStatus()
{
    return loseFlag; 
}

// getter for score
int GameMechs::getScore()
{
    return score; 
}

// setter for exit flag
void GameMechs::setExitTrue()
{
    exitFlag = true; 
}

// setter for input
void GameMechs::setInput(char this_input)
{
    input = this_input; 
}

// clears input 
void GameMechs::clearInput()
{
    input = 0;
}

// setter for lose flag
void GameMechs::setLoseFlag()
{
    loseFlag = true;
    
}

// setter for score
void GameMechs::incrementScore(int value)
{
    score += value; 
}


