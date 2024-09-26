#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Food;

class Player
{
    public:
        enum Dir {STOP, UP, LEFT, DOWN, RIGHT};  // This is the direction state

        Player(GameMechs *thisGMRef, Food *thisFoodRef);
        ~Player();

        // Player position stuff; get and update direction, get position.
        objPosArrayList *getPlayerPos();
        void updatePlayerDir();
        int getDir();

        // To move or to eat? That is the question. (Read the comments on each function within Player.cpp for more details)
        void handleFoodAndMovement(int lengthGain);
        bool isFoodConsumed(int &lengthGain);
        void increasePlayerLength(int lengthGain);
        void movePlayer();

    private:
        objPosArrayList *playerPosList;      
        enum Dir myDir;
        
        void advanceObjectPos(objPos &obj);
        bool IsSnakeSucidal(objPos &nextHeadPos);

        // To refer to GameMechs and Food
        GameMechs *mainGameMechsRef;
        Food *mainFoodRef;
};

#endif