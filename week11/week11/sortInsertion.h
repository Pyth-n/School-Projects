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
   int iInsert, iShift;

   for(int iPivot = num-2; iPivot >= 0; iPivot--)
   {
      T valuePivot =  array[iPivot];
      iInsert = binarySearch(array, valuePivot, iPivot + 1, num - 1);
      iInsert--;
      for(iShift=iPivot;iShift < iInsert; iShift++)
         array[iShift]= array[iShift + 1];
    
      array[iShift]= valuePivot;
    }
   
   
}

/*****************************************************
 * Binary Search
 ****************************************************/
template <class T>
int binarySearch(T array[], T searchItem, int iBegin, int iEnd)
{
   int iMiddle = (iBegin+iEnd)/2;
   

    if(iBegin > iEnd)
       return iBegin;
   
    if(array[iMiddle] == searchItem)
       return iMiddle;
   
    if(searchItem > array[iMiddle])
       return binarySearch(array, searchItem, iMiddle + 1, iEnd);
    else
       return binarySearch(array, searchItem, iBegin, iMiddle - 1);
    

}

#endif // SORT_INSERTION_H
