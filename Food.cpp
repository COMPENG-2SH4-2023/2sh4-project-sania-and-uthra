#include "Food.h"

// Constructor
Food::Food(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef; 
    foodBucket = new objPosArrayList();  
    srand(time(NULL));
}

// Deconstructor
Food::~Food()
{
    delete foodBucket; 
}

// generate 5 random food items
void Food::generateFood(objPosArrayList* blockOff)
{
    /**
        Generate 5 random food items representing symbol '1'
    */
    foodBucket->emptyList(); // empty the list everytime generate food is called
    for (int j = 0; j < 5; j++)
    {
        objPos randPos; 
        bool found; // to check if the randomly generated food pos overlaps with other food or player

        do {
            found = false;
            // Generate random coordinates for the food within the game board
            randPos.setObjPos((rand() % (mainGameMechsRef->getBoardSizeX() - 2)) + 1,
                              (rand() % (mainGameMechsRef->getBoardSizeY() - 2)) + 1,
                              '1');

            // Check if the generated food position overlaps with the player's body segments
            for (int i = 0; i < blockOff->getSize(); i++)
            {
                objPos bodyPos; 
                blockOff->getElement(bodyPos, i); //get the player body pos 
                // Food position matches a player's body segment, found set to true to regenerate food
                if (randPos.isPosEqual(&bodyPos))
                {
                    found = true;
                    break;
                }
            }

            // check if the generated food position overlaps with the existing food items 
            for (int i = 0; i < foodBucket->getSize(); i++)
            {
                objPos existingFood;
                foodBucket->getElement(existingFood, i); // get existing food pos
                // Food position matches existing food, found set to true to regenerate food
                if (randPos.isPosEqual(&existingFood))
                {
                    found = true;
                    break;
                }
            }

        } while (found);

        // food position does not match the player body
        if (!found)
        {
            foodBucket->insertTail(randPos); //insert the random food in the food bucket
        }
    }

    /**
        generate special food item representing symbol '$'
    */
    // Generate 1 or 2 special food items
    int specialFoodCount = (rand() % 2) + 1; // Creates either 1 or 2 special food

    for (int i = 0; i < specialFoodCount; i++)
    {
        objPos specialFoodPos;  
        bool specialFoodGenerated = false; // to check if special food is generated

        do {
            int randIndex = rand() % foodBucket->getSize(); // get random index in the food bucket
            // sets the objPos info for specialFoodPos based on the objPos info of an existing obj
            // at the random index in foodbucket
            foodBucket->getElement(specialFoodPos, randIndex); 

            // Check if the selected position is not already a special food
            if (specialFoodPos.getSymbol() != '$') 
            {
                specialFoodPos.symbol = '$'; // set it to special food
                foodBucket->changeElement(specialFoodPos, randIndex); // change the existing food item to special food in the food bucket
                specialFoodGenerated = true;
            }
        } while (!specialFoodGenerated); 
    }
   
}

// get the food bucket 
objPosArrayList* Food::getFoodPos()
{
    return foodBucket; 
}