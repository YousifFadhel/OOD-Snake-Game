#ifndef FOOD_H //By ensuring that the same header file is included only once, the compiler can reduce the amount of processing it needs to do, which can speed up compilation times.
#define FOOD_H

#include <cstdlib> // rand() and srand()
#include <ctime>

#include "GameMechs.h"
#include "Player.h"
#include "objPos.h"
#include "objPosArrayList.h"


//Global scope macros
#define FOOD_COUNT                          5
#define DEFAULT_FOOD_KIND                   'o'
#define SPECIAL_FOOD_KIND1                  'x'
#define SPECIAL_FOOD_KIND2                  '$'

#define DEFAULT_FOOD_KIND_SCORE             1
#define SPECIAL_FOOD_KIND1_SCORE            10
#define SPECIAL_FOOD_KIND2_SCORE            5

#define DEFAULT_FOOD_KIND_LENGTH_PENALTY    1
#define SPECIAL_FOOD_KIND1_LENGTH_PENALTY   0
#define SPECIAL_FOOD_KIND2_LENGTH_PENALTY   10


class Player; // allows for the food class to reference the player class

class Food
{
    private:
        objPosArrayList *foodBucket;

    public:
        Food(GameMechs *thisGMRef, Player *thisPLRef);
        ~Food();
        
        int foodCount();
        void getFoodPos(objPos &returnPos, int foodIndex);
        void generateFood(GameMechs *thisGMRef, objPosArrayList *blockOff);
        void consumeFood(int foodIndex, int &score, int &lengthGain);
};

#endif