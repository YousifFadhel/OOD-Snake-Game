#include "Player.h"

Player::Player(GameMechs *thisGMRef, Food *thisFoodRef)
{
    playerPosList = new objPosArrayList();
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    objPos head;
    head.setObjPos(mainGameMechsRef->getBoardSizeX() / 2, 
                   mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertTail(head);
}

Player::~Player()
{
    delete playerPosList;
    playerPosList = nullptr;
}

objPosArrayList *Player::getPlayerPos()
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();

    switch (input) {
    case 'W':
    case 'w':
        if (myDir != UP && myDir != DOWN)
            myDir = UP;
        break;
    case 'A':
    case 'a':
        if (myDir != LEFT && myDir != RIGHT)
            myDir = LEFT;
        break;
    case 'S':
    case 's':
        if (myDir != DOWN && myDir != UP)
            myDir = DOWN;
        break;
    case 'D':
    case 'd':
        if (myDir != RIGHT && myDir != LEFT)
            myDir = RIGHT;
        break;
    }
}

int Player::getDir()
{
    // Gets the current direction for printing on screen.
    return myDir;
}

// This function should be self-evident.
void Player::handleFoodAndMovement(int lengthGain)
{
    if (isFoodConsumed(lengthGain)) {
        increasePlayerLength(lengthGain);
    }
    else {
        movePlayer();
    }
}

bool Player::isFoodConsumed(int &lengthGain)
{
    objPos f;
    objPos nextHeadPos;

    // Get the next head pos (to check if food is about to be consumed).
    playerPosList->getHeadElement(nextHeadPos);
    advanceObjectPos(nextHeadPos);

    for (int i = 0; i < mainFoodRef->foodCount(); i++) {
        mainFoodRef->getFoodPos(f, i);    
        // The next head position would result into consuming the food.
        // Consume food and return the length gained to add it to the snake body.
        if ((nextHeadPos.x == f.x) && (nextHeadPos.y == f.y)) {
            int scoreToAdd;        
            mainFoodRef->consumeFood(i, scoreToAdd, lengthGain);
            mainGameMechsRef->incrementScore(scoreToAdd);
            mainFoodRef->generateFood(mainGameMechsRef, playerPosList);

            return true;
        }
    }

    // No food is consumed; do nothing.
    return false;
}

void Player::increasePlayerLength(int lengthGain)
{
    objPos newHead;
    int addedLength = 0;

    do {
        playerPosList->getHeadElement(newHead);

        // Additional food in the way of growth must be consumed as well. This is one hungry snake...
        if (isFoodConsumed(addedLength)) {
            lengthGain += addedLength;
        }

        if (lengthGain > 0){
            // Prepare moving the head according to the commanded input direction.
            advanceObjectPos(newHead);

            // If the head growth will result in sucide, return, as the game is lost. 
            if (IsSnakeSucidal(newHead)) {
                return;
            }

            playerPosList->insertHead(newHead);
            lengthGain--;
        }

    } while (lengthGain > 0);
}

void Player::movePlayer()
{
    objPos o;
    // Move body parts (except head) to be aligned with the previous ones.
    for (int i = playerPosList->getSize() - 1; i > 0; i--) {
        playerPosList->getElement(o, i - 1);
        playerPosList->setElement(o, i);
    }

    // Prepare moving the head according to the commanded input direction .
    playerPosList->getHeadElement(o);
    advanceObjectPos(o);

    if (!IsSnakeSucidal(o)) {
        // At this stage, the snake's head could move without being sucidal.
        // Move the head according to the commanded input direction 
        playerPosList->setElement(o, 0);
    }
}

// PRIVATE FUNCTIONS

void Player::advanceObjectPos(objPos &obj) {
    // This would advance the player body part object to the commanded direction.
    switch (myDir) {
        case UP:
            if (obj.y == 1) {
                obj.y = BOARD_SIZE_Y - 2;
            }
            else {
                obj.y--;
            }
            break;
        case DOWN:
            if (obj.y == BOARD_SIZE_Y - 2) {
                obj.y = 1;
            }
            else {
                obj.y++;
            }
            break;
        case LEFT:
            if (obj.x == 1) {
                obj.x = BOARD_SIZE_X - 2;
            }
            else {
                obj.x--;
            }
            break;
        case RIGHT:
            if (obj.x == BOARD_SIZE_X - 2) {
                obj.x= 1;
            }
            else {
                obj.x++;
            }
            break;
        default:
            break;
    }
}

bool Player::IsSnakeSucidal(objPos &nextheadPos) {
    // Check if the snake's head moving or addition would cause collision with its body.
    objPos e;
    for (int i = playerPosList->getSize() - 1; i > 0; i--) {
        playerPosList->getElement(e, i);
        if ((nextheadPos.x == e.x) && (nextheadPos.y == e.y)) {
            mainGameMechsRef->setLoseTrue();

            return true;
        }
    }

    return false;
}