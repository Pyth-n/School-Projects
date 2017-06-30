/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

template <class T>
void swap(T *array, int first, int second);

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{

   
   for(int iPivot = num; iPivot > 1; iPivot--)
   {
      bool swapped = false;
      for(int iCheck = 0 ; iCheck < iPivot-1; iCheck++)
      {
         if(array[iCheck] > array[iCheck+1])
         {
            swap(array,iCheck, iCheck+1);
            swapped = true;
         }
      }
      
      if(!swapped)
         return;
   }
 

}

template <class T>
void swap(T *array, int first, int second)
{
   T temp = array[first];
   array[first] = array[second];
   array[second] = temp;;
   
}

#endif // SORT_BUBBLE_H
