/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
   BST <T> bst;
   BSTIterator <T> it;
   int i;
   
   //Create the BST from the array
   for(i=0;i < num; i++)
      bst.insert(array[i]);
   
   //Use the iterator put back the BST from begining to end order in the array
   i = 0;
   for(it = bst.begin(); it != bst.end(); ++it)
       array[i++] = *it;
    
   
}


#endif // SORT_BINARY_H
