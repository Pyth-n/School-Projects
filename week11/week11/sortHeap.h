/***********************************************************************
 * Module:
 *    Week 11, Sort Heap
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Heap Sort. Referenced from PDF and
 *    discussion board.
 ************************************************************************/

#ifndef SORT_HEAP_H
#define SORT_HEAP_H

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

   // Non-default constructor
   Heap(T data[], int num)
   {
      this->num = num;
      array = new T[num + 1];

      // Copy contents
      for (int i = 0; i <= num; i++)
      {
         array[i] = data[i];
      }
      heapify(array, num);
   }

   ~Heap() { delete[] array; }
   
   T & getMax() throw (const char *) { return array[1]; } // retrieve the maximum element
   int getNum() { return num; }
   T* getData() { return array; }


   void deleteMax() throw (const char *) {
      array[1] = array[num];
      num--;
      percolateDown(array, 1, num);
   }// delete the top element

   void heapify(T* data, int n)
   {
      int i = n/2;
      for (i; i >= 1; i--)
         percolateDown(data, i, n);
   }
   // create a heap out of array
   void sort(T* a, int n) {
      int i;
      T tmp;

      for (i = n; i >= 2; i--) {
         tmp = a[i];
         a[i] = a[1];
         a[1] = tmp;
         percolateDown(a, 1, i - 1);
      }
   }// destructively sort
   
private:
   
   void percolateDown(T* array, int index, int n)
   {
      T tmp = array[index];
      int j = 2 * index;

      while (j <= n)
      {
         if (j < n && array[j + 1] > array[j])
            j = j + 1;

         if (array[j] > tmp || array[j] == tmp)
         {
            array[j / 2] = array[j];
            j = j * 2;
         }
         else if (tmp > array[j])
            break;
      }
      array[j / 2] = tmp;

   }// fix heap from index down
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
/*
template <class T>

void Heap <T> :: heapify()

{
   
   // percolate all the non-leaf nodes
   for (int i = num / 2; i >= 1; --i)
      percolateDown(i);
   
}
*/
/************************************************
 * HEAP :: PERCOLATE DOWN
 * The item at the passed index may be out of heap
 * order. Take care of that little detail!
 ***********************************************
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
   
}*/

/*****************************************************
* SORT HEAP
* Perform the heap sort
****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
   T sortArray[num + 1];

   for (int i = 0; i < num; i++)
      sortArray[i + 1] = array[i];

   Heap<T>* heap = new Heap<T>(sortArray, num);
   heap->sort(heap->getData(), heap->getNum());

   for (int i = 1; i <= num; i++) {
      array[i - 1] = heap->getData()[i];
   }
}

#endif // SORT_HEAP_H
