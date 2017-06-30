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

   // Delete operator
   ~Heap() { delete[] array; }

   // Getters //
   // retrieve the maximum element
   T & getMax() throw (const char *) { return array[1]; }
   T* getData() { return array; }
   int getNum() { return num; }


   // delete the top element
   void deleteMax() throw (const char *) {
      array[1] = array[num];
      num--;
      percolateDown(array, 1, num);
   }

   // create a heap out of array
   void heapify(T* data, int n);

   // destructively sort
   void sort(T* a, int n);

private:
   // fix heap from index down
   void percolateDown(T* array, int index, int n);

   // swap two items, inline for speed
   void swap(int i1, int i2)
   {
      T temp = array[i1];
      array[i1] = array[i2];
      array[i2] = temp;
   }

   T * array; // the array
   int num; // the number of items in the array

};

/*****************************************************
* SORT
* Destructively sort
****************************************************/
template<class T>
void Heap<T>::sort(T * a, int n)
{
   int i;
   T tmp;

   for (i = n; i >= 2; i--) {
      tmp = a[i];
      a[i] = a[1];
      a[1] = tmp;
      percolateDown(a, 1, i - 1);
   }
}

/*****************************************************
* HEAPIFY
* Creates heap
****************************************************/
template <class T>
void Heap<T> ::heapify(T* data, int n)
{
   int i = n / 2;
   for (i; i >= 1; i--)
      percolateDown(data, i, n);
}

/*****************************************************
* PERCOLATE DOWN
* Fix heap order
****************************************************/
template<class T>
void Heap<T> ::percolateDown(T* array, int index, int n)
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
}

/*****************************************************
* SORT HEAP
* Perform the heap sort
****************************************************/
template <class T>
void sortHeap(T array[], int num)
{
   // Fix index and add an extra space
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
