#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
    aList = new objPos [ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList == sizeArray)
        return;

    for (int i = sizeList; i > 0; i--)
        aList[i] = aList[i - 1];
    
    aList[0] = thisPos;
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList == sizeArray)
        return;

    aList[sizeList] = thisPos;
    sizeList++;
}

void objPosArrayList::removeHead()
{
    if (sizeList == 0)
        return;

    for (int i = 0; i < sizeList - 1; i++)
        aList[i] = aList[i + 1];  // Shiting all elements towards the tail to create space at the head

    sizeList--;
}

void objPosArrayList::removeTail()
{
    if (sizeList == 0)
        return;

    sizeList--;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos = aList[0];
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos = aList[sizeList - 1];
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos = aList[index];
}

void objPosArrayList::setElement(objPos &returnPos, int index)
{
    if (index < sizeList){
        aList[index] = returnPos;
    }
}