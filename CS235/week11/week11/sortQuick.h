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
   // Do nothing
   if (num <= 1)
      return;

   int iUp = 0;
   int iEnd = num - 1;
   int iDown = iEnd;

   // Find pivot
   T pivotValue = array[iEnd / 2];
   
   // Quickly sorts
   while (iUp <= iDown)
   {
      // Advance up
      while (iUp <= iEnd && pivotValue > array[iUp])
         iUp++;

      // Advance down
      while (iDown >= 0 && array[iDown] > pivotValue)
         iDown--;

      // Swap
      if (iUp <= iDown)
      {
         T tmp = array[iUp];
         array[iUp++] = array[iDown];
         array[iDown--] = tmp;
      }
   }

   // Calls recursively
   sortQuick(array, iUp);
   sortQuick(array + iUp, iEnd - iUp + 1);
}


#endif // SORT_QUICK_H
