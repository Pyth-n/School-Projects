/***********************************************************************
 * Module:
 *    Week 11, Sort Quick
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Quick Sort
 ************************************************************************/

#ifndef SORT_QUICK_H
#define SORT_QUICK_H

/*****************************************************
 * SORT QUICK
 * Perform the quick sort
 ****************************************************/
template <class T>
void sortQuick(T array[], int num)
{
   
   /*   Pseudo Code
    
    IFn≤1
      RETURN 
   
    iDown iEnd n – 1
    iUp 0 
    pivotValue array[iEnd/2]
    
    WHILE iUp ≤ iDown
    {
      WHILE iUp ≤ iEnd and pivotValue > array[iUp]
         iUp++
      WHILE iDown ≥ 0 and array[iDown] > pivotValue
         iDown—
    
      IF iUP ≤ iDown
         SWAP array[iUp] array[iDown]
    }
    
    sortQuick(array, iUp) 
    sortQuick(array + iUp, iEnd – iUp + 1
    
    
    */
   
   
}


#endif // SORT_QUICK_H
