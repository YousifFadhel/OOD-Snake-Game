#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs() // Default constuctor; not used.
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;

    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    loseFlag = false;

    boardSizeX = boardX;
    boardSizeY = boardY;
}

// No need to define a destructor.

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

char GameMechs::getInput()
{
    return input;
}

void GameMechs::setInput(char this_input)
{
   input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::incrementScore()
{
    incrementScore(1); // Default points earned is set to 1.
}

void GameMechs::incrementScore(int scoreToAdd)
{
    score += scoreToAdd;
}

int GameMechs::getScore()
{
    return score;
}

/* ENDING THE GAME
    
    How this works:
        Initially exit and lose flags are false.
        When ESC is hit, exit is set to true.
        If exit is true, game ends and prints exiting message.
        When lose is true, game ends and prints losing message.
        In both cases, the score is printed.
*/

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseTrue()
{
    loseFlag = true;
}

void GameMechs::endGame()
{
    if (input == ESC_KEY) {
        GameMechs::setExitTrue();
    }
}

void GameMechs::endMessage()
{
    if (getExitFlagStatus()) {
        MacUILib_printf("User has manually ended the game. Your score was: %d.\n", getScore());
    }
    else if(getLoseFlagStatus()) {
        MacUILib_printf("Don't kill yourself... Your score was: %d.\n", getScore());
    }
}