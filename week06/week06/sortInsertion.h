/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Jeffry Simpson, David Perez
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   Node <T> *nCurrent, *nHead;
   
  for(int i=0; i < num; i++)
  {
     if(nCurrent == NULL)
     {
         insert(array[i], nCurrent);
         nHead = nCurrent;
     }
     else
     {
        nCurrent = nHead;
        while((array[i] > nCurrent->data) && (nCurrent->pNext != NULL))
        {
           nCurrent = nCurrent->pNext;
        }
        
        insert(array[i],nCurrent,false);
     }
  }
   nCurrent = nHead;
         
   for(int i=0; i < num; i++)
   {
       array[i] = nCurrent->data;
       nCurrent = nCurrent->pNext;
   }
   
}

#endif // INSERTION_SORT_H

