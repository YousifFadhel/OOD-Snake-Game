#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

#define BOARD_SIZE_X 30
#define BOARD_SIZE_Y 15
#define ESC_KEY 27

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;
        
        int boardSizeX;
        int boardSizeY;

    public:
        GameMechs();
        GameMechs(int boardX, int boardY);
        
        int getBoardSizeX();
        int getBoardSizeY();

        char getInput();
        void setInput(char this_input);
        void clearInput();

        void incrementScore();
        void incrementScore(int scoreToAdd);
        int getScore();

        bool getExitFlagStatus();
        void setExitTrue();
        bool getLoseFlagStatus();
        void setLoseTrue();

        void endGame();
        void endMessage();
};

#endif