/***********************************************************************
 * Module:
 *    Week 11, Sort Insertion
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>

template <class T>
int binarySearch(T array[], T searchItem, int iBegin, int iEnd);

/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
   /*   Pseudo Code

    FOR iPivot n-2 ... 0
    {
      valuePivot array[iPivot];
      iInsert binarySearch(array, valuePivot, iPivot + 1, n – 1) 
      iInsert--
      for iShift iPivot ... iInsert
         array[iShift] array[iShift + 1] 
    
      array[iShift] valuePivotpivot;
    }
    
    
    */
   
   
}

/*****************************************************
 * Binary Search
 ****************************************************/
template <class T>
int binarySearch(T array[], T searchItem, int iBegin, int iEnd)
{
   /*   Pseudo Code
   
    iMiddle (iBegin + iEnd)/2
    IF iBegin > iEnd
      RETURN iBegin
    IF array[iMiddle] = searchItem
      RETURN iMiddle
    IF search > array[iMiddle]
      RETURN binarySearch(array, search, iMiddle + 1, iEnd)
    ELSE
      RETURN binarySearch(array, search, iBegin, iMiddle – 1)
    
    */
}

#endif // SORT_INSERTION_H
