/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H


/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
      //Outer loop  Set Pivot to end and move down
   for(int iPivot = num-1; iPivot > 0; iPivot--)
   {
      int iLargest = 0;
      //Inner Loop  Set check at beginning and move toward pivot
      for(int iCheck = 0; iCheck < iPivot; iCheck++)
      {
         if(array[iCheck] > array[iLargest])   //If lower item is larger than later item adjust
            iLargest = iCheck;
      }
    
      if(array[iLargest] > array[iPivot])  //swap items
         swap(array,iLargest, iPivot);
    }

   
}

#endif // SORT_SELECTION_H
