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
    // list is at max capacity 
    if(listSize == arrayCapacity)
    {
        return; // do not add any elements
    }
    aList[listSize].setObjPos(thisPos); 
    listSize++; 
}

void objPosArrayList::removeHead()
{
    // empty list 
    if(listSize == 0){
        return;  // do not remove elements
    }

    for(int i = 1; i <listSize; i++)
    {
        aList[i-1].setObjPos(aList[i]); 
    }
    listSize--; 
}

void objPosArrayList::removeTail()
{
    // empty list
    if(listSize == 0){
        return; // do not remove elements
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

void objPosArrayList::emptyList()
{
    listSize = 0; // reset the list size to 0
}

void objPosArrayList::changeElement(objPos &newPos, int index)
{
    if (index >= 0 && index < listSize) {
        aList[index].setObjPos(newPos); // change the element at the specified index to newPos element 
    }
}