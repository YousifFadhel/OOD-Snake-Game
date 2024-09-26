#include "Food.h" // including header file

Food::Food(GameMechs* thisGMRef, Player* thisPLRef) // this is the constructor function of the Food class
{
    foodBucket = new objPosArrayList(); // dynamically allocate memory on the heap for objPosArrayList
}

Food::~Food() // this is the destructor function of the Food class
{
    delete foodBucket; // free heap
    foodBucket = nullptr; // prevent dangling pointers (occurs if the pointer is accessed after memory is freed)
}

int Food::foodCount()
{
    if (foodBucket == nullptr) { // check if the food bucket is empty
        return 0; // if no food return 0
    }
    
    return foodBucket->getSize(); // accessing the method getsize, AKA getting the size of the foodbucket. Food bucket is a pointer thus use (->) not ().)
}

void Food::getFoodPos(objPos &returnPos, int foodIndex)
{
    if ((foodIndex >= 0) && (foodIndex < foodBucket->getSize())){ // if foodindex is 0 AND foodindex is less than the size of foodbucket
        foodBucket->getElement(returnPos, foodIndex); // access the position of the food item and store it in returnPos
    }
}

void Food::generateFood(GameMechs* thisGMRef, objPosArrayList *blockOff)
{
    srand(time(NULL)); //Seed the RNG with the current time to ensure different random numbers on every run
    
    if (foodBucket->getSize() <= 0){ //Checking if the foodbucket is empty / no food has been generated yet

        // These will hold flags for the purpose of generating new special foods.
        bool specialFood1 = true;
        bool specialFood2 = true;

        while (foodBucket->getSize() < FOOD_COUNT) { // While the number of items in foodbucket is less than the global variable FOOD_COUNT which is 5.
            bool found;
            objPos newFoodPos;

            // Enter once, then repeat until a valid position for the new food is found
            do {
                found = true;

                // rand() % N generates random number between 0 and N-1
                newFoodPos.x = 1 + rand() % (thisGMRef->getBoardSizeX() - 2); // Default x-range = [0, 29], foodPos.x = [1, 28], to avoid boarders
                newFoodPos.y = 1 + rand() % (thisGMRef->getBoardSizeY() - 2); // Default y-range = [0, 14], foodPos.y = [1, 13], to avoid boarders

                if (blockOff != nullptr) {
                    // Make sure the random position for the new food does not overlap with the snake
                    for (int i = 0; i < blockOff->getSize(); i++) {
                        objPos o;
                        blockOff->getElement(o, i);
                        if (o.x == newFoodPos.x && o.y == newFoodPos.y) {
                            found = false; // ensure no food spawns on the snakes body
                            break;
                        }
                    }
                }
                if (foodBucket != nullptr) {
                    // Make sure the random position for the new food does not overlap with existing food in the bucket.
                
                    for (int i = 0; i < foodBucket->getSize(); i++) {
                        objPos existedFoodPos;
                        foodBucket->getElement(existedFoodPos, i);
                        if (existedFoodPos.x == newFoodPos.x && existedFoodPos.y == newFoodPos.y) {
                            found = false;
                            break;
                        }
                    }
                }
            } while (!found);


            int generateRandomSpecialFood;
            generateRandomSpecialFood = rand() % 2; // produces either 0 or 1 randomly

            // Randomize the probability of having special food,
            // provided they are not already generated in this iteration.
            if (specialFood1 && generateRandomSpecialFood) {
               specialFood1 = false;
               newFoodPos.symbol = SPECIAL_FOOD_KIND1;
            }
            else if (specialFood2 && generateRandomSpecialFood) {
               specialFood2 = false;
               newFoodPos.symbol = SPECIAL_FOOD_KIND2;
            }
            else {
              newFoodPos.symbol = DEFAULT_FOOD_KIND;
            }
            foodBucket->insertHead(newFoodPos); //add the new food item to the front of the foodbucket list
        }
    }
}

void Food::consumeFood(int foodIndex, int& score, int& lengthGain)
{
    score = 0;
    if ((foodIndex >= 0) && foodIndex < foodBucket->getSize()) { // ensure the index of food being consumed is non-negative and within the bounds of foodbucket
        objPos food; 
        foodBucket->getElement(food, foodIndex); //Retrieve food item!

        // Score and length gain penalty are subject to the food type being consumed.
        switch (food.symbol)
        {
            case SPECIAL_FOOD_KIND1:
                score = SPECIAL_FOOD_KIND1_SCORE; //Special food type 1 adds 10 to your score, with no length gain! :D
                lengthGain = SPECIAL_FOOD_KIND1_LENGTH_PENALTY; 
                break;
            case SPECIAL_FOOD_KIND2:
                score = SPECIAL_FOOD_KIND2_SCORE; // Special food type 2 adds 5 to your score but 10 to your length! D:
                lengthGain = SPECIAL_FOOD_KIND2_LENGTH_PENALTY;
                break; 
            default:
                score = DEFAULT_FOOD_KIND_SCORE;
                lengthGain = DEFAULT_FOOD_KIND_LENGTH_PENALTY;
                break;
        }
        // We need to remove the consumed food from our food bucket.
        // Once all foods in the bucket are consumed, a new batch will be generated.

        // shift all food items in the list after foodIndex one position to the left, retrieve the food 
        for (int i = foodIndex; i < foodBucket->getSize() - 1; i++) {
            foodBucket->getElement(food, i+1); //retrieve food item at i+1 and store in food
            foodBucket->setElement(food, i); //set food to new position i
        }
        foodBucket->removeTail(); //remove remaining duplicate item
    }   
}