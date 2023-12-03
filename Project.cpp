#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

//bool exitFlag;
GameMechs* myGameMech; 
Player* myPlayer; 
Food* myFood; 

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    while (!myGameMech->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGameMech = new GameMechs(30,15); // 30x15 game board
    myFood = new Food(myGameMech);  
    myPlayer = new Player(myGameMech, myFood); 

    objPosArrayList* playerBody = myPlayer->getPlayerPos(); // create a obj array for player body 
    myFood->generateFood(playerBody); // generate food based on player location 

}

void GetInput(void)
{
    myGameMech->getInput(); 
}

void RunLogic(void)
{
    // exit game by pressing "ESC"
    if(myGameMech->getInput() == 27)
    {
        myGameMech->setExitTrue(); 
    }
    
    // update the FSM and move the player
    // use wasd keys in lower case to move the player
    myPlayer->updatePlayerDir(); 
    myPlayer->movePlayer(); 

    myGameMech->clearInput(); // so to not repeatedly process input;  

}

void DrawScreen(void)
{
     MacUILib_clearScreen();

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPosArrayList* foodItems = myFood->getFoodPos();

    for (int y = 0; y < myGameMech->getBoardSizeY(); ++y)
    {
        for (int x = 0; x < myGameMech->getBoardSizeX(); ++x)
        {
            bool isPlayerBody = false;
            bool isFoodItem = false;

            // Check if the current position corresponds to a player body segment
            for (int k = 0; k < playerBody->getSize(); ++k)
            {
                objPos tempBody;
                playerBody->getElement(tempBody, k);
                if (tempBody.x == x && tempBody.y == y)
                {
                    MacUILib_printf("%c", tempBody.symbol);
                    isPlayerBody = true;
                    break;
                }
            }

            if (isPlayerBody) continue; // Skip drawing if it's a player body segment

            // Check if the current position corresponds to a food item
            for (int i = 0; i < foodItems->getSize(); ++i)
            {
                objPos tempItem;
                foodItems->getElement(tempItem, i);
                if (tempItem.x == x && tempItem.y == y)
                {
                    MacUILib_printf("%c", tempItem.symbol);
                    isFoodItem = true;
                    break; 
                }
            }

            if (isFoodItem) continue; // Skip drawing if it's a food item

            // Draw borders or empty space if not a player body segment or food item
            if (x == 0 || x == myGameMech->getBoardSizeX() - 1 || y == 0 || y == myGameMech->getBoardSizeY() - 1)
            {
                MacUILib_printf("%c", '#'); // Render borders
            }
            else
            {
                MacUILib_printf("%c", ' '); // Empty space inside the borders
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d\n", myGameMech->getScore());

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();  

    /// display lose flag message for self collision
    if (myGameMech->getLoseFlagStatus())
    {
         MacUILib_printf("\nSNAKE SUICIDE! YOU LOST :("); 
    }  
  
    MacUILib_uninit();

    delete myGameMech;
    delete myFood;
    delete myPlayer; 
     
}
