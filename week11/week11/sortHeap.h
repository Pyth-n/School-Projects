/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Heap Sort
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

/*****************************************************
 * SORT HEAP
 * Perform the heap sort
 ****************************************************/
template <class T>
void sortHeap(T array[], int num)
{

}

/*************************************************
 * HEAP
 * Create a heap. This is like a "pile" except
 * considerably less organized
 *************************************************/

template <class T>
class Heap
{
   
public:
   
   // constructors
   Heap() : num(0), array(NULL) {}
   Heap(T * array, int num);
   
   
   T & getMax() throw (const char *); // retrieve the maximum element
   void deleteMax() throw (const char *); // delete the top element
   void heapify(); // create a heap out of array
   void sort(); // destructively sort
   
private:
   
   void percolateDown(int index); // fix heap from index down
   void swap(int i1, int i2) // swap two items, inline for speed
   {
      
      T temp = array[i1];
      array[i1] = array[i2];
      array[i2] = temp;
      
   }
   
   T * array; // the array
   int num; // the number of items in the array
   
};

/**********************************************
 * HEAP :: HEAPIFY
 * Create a heap out of the current array
 *********************************************/

template <class T>

void Heap <T> :: heapify()

{
   
   // percolate all the non-leaf nodes
   for (int i = num / 2; i >= 1; --i)
      percolateDown(i);
   
}

/************************************************
 * HEAP :: PERCOLATE DOWN
 * The item at the passed index may be out of heap
 * order. Take care of that little detail!
 ************************************************/

template <class T>
void Heap <T> :: percolateDown(int index)
{
   
   assert(index >= 1 && index <= num);
   
   // do nothing if we are a leaf
   int indexLeft = index * 2;
   if (indexLeft > num)
      return;
   
   int indexRight = indexLeft + 1;
   
   // if right is the worst of the two, then go that way
   if (indexRight <= num && // there is an index right
       array[indexRight] > array[indexLeft] && // right is bigger than left
       array[indexRight] > array[index]) // right is bigger than parent
   {
      swap(index, indexRight);
      percolateDown(indexRight);
      
   }
   
   // if the left is the worst of the two, then go that way
   else if (array[indexLeft] > array[index]) // the left is bigger...
   {
      
      swap(index, indexLeft);
      percolateDown(indexLeft);
   }
   
   // otherwise do nothing
   
}


#endif // SORT_HEAP_H
