#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib> // provides srand() and rand()
#include <time.h>  // ctime 

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class GameMechs
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        char input;
        bool exitFlag;
        bool loseFlag; 
        int score; 
        
        int boardSizeX;
        int boardSizeY;

    public:
        // constructors 
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        // getters and setters 
        bool getExitFlagStatus();
        void setExitTrue();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        int getBoardSizeX();
        int getBoardSizeY();

        bool getLoseFlagStatus();
        void setLoseFlag();

        int getScore();
        void incrementScore(int value); 
      

};

#endif