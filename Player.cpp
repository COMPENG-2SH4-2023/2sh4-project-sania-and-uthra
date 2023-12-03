#include "Player.h"

// constructor 
Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    foodRef = thisFood; 

     // more actions to be included
    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2,
                      mainGameMechsRef->getBoardSizeY()/2,
                      'o');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos); 

}

// destructor 
Player::~Player()
{
    // delete any heap members here
    delete playerPosList; 
}

// getter for player pos 
objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPosList; 

}

// updates player direction
void Player::updatePlayerDir()
{

    char input = mainGameMechsRef->getInput(); 

    // PPA3 input processing logic 
    switch(input) 
    {
        case 'w':
            if (myDir != UP && myDir != DOWN)
                myDir = UP;
            break;

        case 'a':
            if (myDir != LEFT && myDir != RIGHT)
                myDir = LEFT; 
            break;

        case 's':
            if (myDir != UP && myDir != DOWN)
                myDir = DOWN; 
            break;

        case 'd':
            if (myDir != LEFT && myDir != RIGHT)
                myDir = RIGHT; 
            break;
            
        default:
            break; 
    }

}

// moves player based on FSM mode
void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    // Retrieve current head position
    objPos currHead;
    playerPosList->getHeadElement(currHead);

    switch (myDir) {
        case UP:
            currHead.y--;
            if (currHead.y <= 0) // If the snake hits the upper border
                currHead.y = mainGameMechsRef->getBoardSizeY() - 2; // Wrap to the bottom
            break;

        case DOWN:
            currHead.y++;
            if (currHead.y >= mainGameMechsRef->getBoardSizeY() - 1) // If the snake hits the bottom border
                currHead.y = 1; // Wrap to the top
            break;

        case LEFT:
            currHead.x--;
            if (currHead.x <= 0) // If the snake hits the left border
                currHead.x = mainGameMechsRef->getBoardSizeX() - 2; // Wrap to the right
            break;

        case RIGHT:
            currHead.x++;
            if (currHead.x >= mainGameMechsRef->getBoardSizeX() - 1) // If the snake hits the right border
                currHead.x = 1; // Wrap to the left
            break;

        case STOP:
        default:
            break;
    }

    // self collision, set both flags true
    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag(); 
        mainGameMechsRef->setExitTrue(); 
    }

    // no self collision 
    else
    {
        // check if any food is consumed 
        if (checkFoodConsumption())
        {
            // check if special food is consumed 
            // Special food is represented by "$"
            if (checkSpecialFoodConsumption())
            {
                mainGameMechsRef->incrementScore(10); // only increment the score by 10
                foodRef->generateFood(playerPosList); // generate new food
            }

            // special food is not consumed
            // normal food is represented by "1"
            else 
            {
                increasePlayerLength();   // increase the player length by 1
                mainGameMechsRef->incrementScore(1); // increase the score by 1;  
                foodRef->generateFood(playerPosList); // generate new food
            }
        }
        
        // Insert new head position
        playerPosList->insertHead(currHead);
        // Remove tail position to maintain snake length
        playerPosList->removeTail();
    }
    
}


// checks for food consumption
bool Player::checkFoodConsumption()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead); // get head pos

    objPosArrayList* foodItems = foodRef->getFoodPos(); // get food bucket
    
    // Check if the current head position overlaps with the food position
    for (int i = 0; i < foodItems->getSize(); i++)
    {
        objPos currFood;
        foodItems->getElement(currFood, i); // get food item in the bucket
        // head collides with the food item 
        if (currHead.isPosEqual(&currFood))
        {
            return true; // return true for food consumption
        } 
    }
    return false; // no food consumed 
}


// checks for special food consumption 
bool Player::checkSpecialFoodConsumption()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead); // get head pos

    objPosArrayList* foodItems = foodRef->getFoodPos(); // get food bucket 
    
    // Check if the current head position overlaps with the food position
    for (int i = 0; i < foodItems->getSize(); i++)
    {
        objPos currFood;
        foodItems->getElement(currFood, i); // get food item in bucket
        // head collides with special food item 
        if (currHead.isPosEqual(&currFood) && currFood.symbol == '$')
        {
            return true; // return true for special food consumption
        } 
    }
    return false; // no special food consumed
}

// increases player lenght 
void Player::increasePlayerLength()
{
    objPos currHead;
    playerPosList->getHeadElement(currHead); 

    // Insert the head again to increase the length of the snake
    playerPosList->insertHead(currHead); 
}

// checks if snake ran into itself
bool Player::checkSelfCollision()
{
    objPos currHead; 
    playerPosList->getHeadElement(currHead); // get head pos
    objPos bodySegment; 

    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(bodySegment, i); // get body segment  
        // head collides with body segment
        if (currHead.isPosEqual(&bodySegment)) 
        {
            return true; 
        } 
    }
    return false;
}

