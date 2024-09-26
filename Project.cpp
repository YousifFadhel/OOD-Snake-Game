#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs* gameMechs;
Player* playerMechs;
Food* foodMechs;

// Function Prototypes
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while(gameMechs->getExitFlagStatus() == gameMechs->getLoseFlagStatus()) // Both flags are false. Only one can be true at a time, so game will end with either manual exit or loss. End game message is dependent on which flag is set to true.
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

    gameMechs = new GameMechs(BOARD_SIZE_X, BOARD_SIZE_Y); // Very important to create the GameMechanics object first.
    foodMechs = new Food(gameMechs, playerMechs);                // Food relies on GameMechanics...
    playerMechs = new Player(gameMechs, foodMechs);              // ... and Player relies on both.
}

void GetInput(void)
{
    // Get the keystroke input from user.
    if (MacUILib_hasChar() != 0) {
        gameMechs->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    int lengthGain;
    foodMechs->generateFood(gameMechs, playerMechs->getPlayerPos());
    playerMechs->updatePlayerDir();
    playerMechs->handleFoodAndMovement(lengthGain);
    gameMechs->endGame();
    gameMechs->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    char directionText[5][6] = {"STOP", "UP", "LEFT", "DOWN", "RIGHT" }; // Print direction on screen. Must be in the same order as enum Dir as defined in Player.h.

    // BEGINNING OF DRAWING THE MAP

    int i, j;
    char drawMap[gameMechs->getBoardSizeY()][gameMechs->getBoardSizeX()] = {0}; // Build rows first; Y goes before X.

    // Assigns border and blank characters to board
    for (i = 0; i < gameMechs->getBoardSizeY(); i++) {
        for (j = 0; j < gameMechs->getBoardSizeX(); j++) {
            if (i == 0 || j == 0 || i == gameMechs->getBoardSizeY() - 1 || j == gameMechs->getBoardSizeX() - 1) {
                drawMap[i][j] = '#';
            }
            else {
                drawMap[i][j] = ' ';
            }
        }
    }

    // Assigns player to board
    if (playerMechs != nullptr) {
        objPosArrayList* playerPosList = playerMechs->getPlayerPos();
        if (playerPosList != nullptr) {
            objPos o;
            for (int i = 0; i < playerPosList->getSize(); i++) {
                playerPosList->getElement(o, i);
                drawMap[o.y][o.x] = o.getSymbol();
            }
        }
    }

    // Assigns food to board
    if (foodMechs != nullptr) {
        for (i = 0; i < foodMechs->foodCount(); i++){
            objPos f;
            foodMechs->getFoodPos(f, i);
            drawMap[f.y][f.x] = f.getSymbol();
        }
    }

    // Prints board
    for (i = 0; i < gameMechs->getBoardSizeY(); i++) {
        for (j = 0; j < gameMechs->getBoardSizeX(); j++) {
            MacUILib_printf("%c", drawMap[i][j]);
        }
        MacUILib_printf("\n");
    }

    // END

    MacUILib_printf("Direction: %s\nScore: %d\n", directionText[playerMechs->getDir()], gameMechs->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();    

    gameMechs->endMessage();

    delete gameMechs;
    delete playerMechs;
    delete foodMechs;

    MacUILib_uninit();
}