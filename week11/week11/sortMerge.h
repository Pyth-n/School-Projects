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
void merge(T destination[], int iBegin1, int iBegin2, int iEnd2, T source[]);

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{
   /*   Pseudo Code
    source array
    
    DO
      numIterations 0
      WHILE iBegin1 < n
         numIterations++
         FOR iEnd1 iBegin1 + 1 ... n or !(source[iEnd1 – 1] > source[iEnd1]) 
            iBegin2 iEnd1 + 1
    
         FOR iEnd2 iBegin2 + 1 ... n or !(source[iEnd2 – 1] > source[iEnd2])
            IF iBegin2 < n
               merge(destination, iBegin1, iBegin2, iEnd2, source)
            iBegin1 iEnd2
    
         SWAP source, destination
    
    WHILE numMerges > 1
    
    IF array ≠ source 
      FOR i 0 ... n-1
         array[i] source[i]
    
    
    */
   
   
}

template <class T>
void merge(T destination[], int iBegin1, int iBegin2, int iEnd2, T source[])
{
   
   /*   Pseudo Code
       
   iEnd1 = iBegin2 – 1
   i1 = iBegin1
   i2 = iBegin2
   
   FOR iDestination 0 ... iEnd2 – iBegin1 + 1
      IF i1 ≤ iEnd1 and (i2 = iEnd2 or source[i2] > source[i1])
         destination[iDestination] source[i1++]
      ELSE
         destination[iDestination] source[i2++]
       
   */
      
}


#endif // SORT_MERGE_H
