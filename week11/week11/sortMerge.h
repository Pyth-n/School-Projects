/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H


template <class T>
void merge(T arr[], int l, int m, int r);

template <class T>
void mergeSort(T array[], int ibegin, int iEnd);

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
   mergeSort(array,0,num-1);
   
}

template <class T>
void mergeSort(T array[], int iBegin, int iEnd)
{
   if (iBegin < iEnd)
   {
      // get mid point
      int iMid = iBegin+(iEnd-iBegin)/2;
      
      // Sort first and second halves
      mergeSort(array, iBegin, iMid);
      mergeSort(array, iMid+1, iEnd);
      
      //Run the merge
      merge(array, iBegin, iMid, iEnd);
   }
}


template <class T>
void merge(T array[], int iBegin, int iMid, int iEnd)
{
   int i, j, k;  //loop counters
   int iSub1 = iMid - iBegin + 1;
   int iSub2 =  iEnd - iMid;
   
   /* create temp arrays */
   T leftSub[iSub1], rightSub[iSub2];
   
   /* Copy data to temp arrays L[] and R[] */
   for (i = 0; i < iSub1; i++)
      leftSub[i] = array[iBegin + i];
   for (j = 0; j < iSub2; j++)
      rightSub[j] = array[iMid + 1+ j];
   
   /* Merge the temp arrays back into arr[l..r]*/
   i = 0; // Initial index of first subarray
   j = 0; // Initial index of second subarray
   k = iBegin; // Initial index of merged subarray
   while (i < iSub1 && j < iSub2)
   {
      if (rightSub[j] > leftSub[i])
         array[k++] = leftSub[i++];
      else
         array[k++] = rightSub[j++];
   }
   
   /* Copy the remaining elements of L[], if there
    are any */
   while (i < iSub1)
      array[k++] = leftSub[i++];
   
   /* Copy the remaining elements of R[], if there
    are any */
   while (j < iSub2)
      array[k++] = rightSub[j++];

}

//Merge and MergeSort used from http://www.geeksforgeeks.org/merge-sort/


#endif // SORT_MERGE_H
