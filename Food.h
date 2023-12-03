#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{
    private:
        objPosArrayList* foodBucket; // reference to food bucket
        GameMechs* mainGameMechsRef; // reference to main game mechanics

    public:
        Food(GameMechs* thisGMRef);
        ~Food();

        void generateFood(objPosArrayList* blockOff); // method to generate random food
        objPosArrayList* getFoodPos(); // getter for food bucket 
};
#endif