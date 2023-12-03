#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0; 
    arrayCapacity = ARRAY_MAX_CAP; 
    aList = new objPos[ARRAY_MAX_CAP]; // 256 elements on the heap
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // delete all instances
}

int objPosArrayList::getSize()
{
    return listSize; 
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // list size is at max capacity 
    if(listSize == arrayCapacity)
    {
        return; // do not add any elements
    }

    for(int i=listSize; i>0; i--)
    {
        aList[i].setObjPos(aList[i-1]); // shuffle all the elements towards the tail
    }
    aList[0].setObjPos(thisPos);
    listSize++;  
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return; 
    }
    aList[listSize].setObjPos(thisPos); 
    listSize++; 
}

void objPosArrayList::removeHead()
{
    if(listSize == 0){
        return;  
    }

    for(int i = 1; i <listSize; i++)
    {
        aList[i-1].setObjPos(aList[i]); 
    }
    listSize--; 
}

void objPosArrayList::removeTail()
{
    if(listSize == 0){
        return; 
    }
    listSize--; 
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[listSize-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    if (index >= 0 && index < listSize) {
        returnPos.setObjPos(aList[index]);
    }
}