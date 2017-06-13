/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Helfrich, CS 235
 * Author:
 *    
 * Summary:
 *    
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include <stack>
#include "bnode.h"

// Iterators prototypes
template <class T>
class BSTIterator;

template <class T>
class BST
{
private:
   BinaryNode<T> * pRoot;


public:
   BST() : pRoot(NULL){}
   BST(const BST<T> & rhs) throw (const char *);
   
   ~BST(){clear();}

   //Operator =
   BST <T> & operator = (const BST <T> & rhs) throw(const char *);
   
   //inLine functions
   int size()     { return pRoot->size(); }
   bool empty()   const { return pRoot == NULL; }
   void clear()
   {  if(pRoot)
         deleteBinaryTree(pRoot);
      pRoot = NULL;
   }
   
   //Function
   void insert(const T & t) throw (const char *);
   
      //Iterator functions
   void remove(BSTIterator<T> & it);
   BSTIterator<T> find(const T & t);
   
   // iterators
   BSTIterator <T> begin();
   BSTIterator <T> end() { return BSTIterator <T> (NULL); }
   BSTIterator <T> rbegin();
   BSTIterator <T> rend() { return BSTIterator <T> (NULL); }

};

/************************************************
 * Copy Constructor
 * Used to copy one list to the other
 ***********************************************/
template <class T>
BST <T> :: BST(const BST <T> & rhs) throw (const char *)
{

   *this = rhs;  //Use assignment operator
   
}

/**********************************************
 * BST :: assignment operator
 * Copy one list onto another
 *********************************************/
template <class T>
BST <T> & BST <T> :: operator = (const BST <T> & rhs) throw (const char *)
{
   
   //Verify we got something to copy
   if (NULL != rhs.pRoot)
   {
      // clear();
      
      try
      {
         // allocate a new head
         pRoot = new BinaryNode<T>(rhs.pRoot->data);
         
         pRoot->pLeft =  copyBTree(rhs.pRoot->pLeft);
         
         if(pRoot->pLeft != NULL)
            pRoot->pLeft->pParent = pRoot;
            
            pRoot->pRight = copyBTree(rhs.pRoot->pRight);
            if(pRoot->pRight != NULL)
               pRoot->pRight->pParent = pRoot;
               
               }
      catch (bad_alloc)
      {
         throw "ERROR: unable to allocate a new node for this tree.";
      }
   }
   else
      pRoot = rhs.pRoot;  //Set Copy Node to Null to match RHS
      
      // return the new buffer
   return *this;
}

/************************************************
 * Insert function
 * Used to insert a new node into the tree
 ***********************************************/
template <class T>
 void BST <T> :: insert(const T & item) throw (const char *)
{
   try
   {
      BinaryNode<T> * locptr = pRoot;
      BinaryNode<T> * parent = 0;
      
      while (locptr != NULL  ) {
         parent = locptr;
         if (item < locptr->data)
            locptr = locptr->pLeft;
            else
               locptr = locptr->pRight;
               }
      
      locptr = new BinaryNode<T>(item);
      if(parent == NULL)
         pRoot = locptr;
         else if (item < parent->data)
         {
            parent->pLeft = locptr;
            locptr->pParent = parent;
         }
         else
         {
            parent->pRight = locptr;
            locptr->pParent = parent;
         }
         
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for this tree.";
   }
}

/************************************************
 * Find function
 * Used to find a node from the tree
 ***********************************************/
template <class T>
BSTIterator <T> BST <T> :: find(const T & t)
{
   BinaryNode<T> * pNode = pRoot;
   bool bFound = false;
   
   while(!bFound && pNode != NULL)
   {
      if(t < pNode->data)
         pNode = pNode->pLeft;
      else if (pNode->data < t)
         pNode = pNode->pRight;
      else
         bFound=true;
   }
   if(bFound)
      return pNode;
   else
      return end();
}



/************************************************
 * Erase function
 * Used to erase a node from the tree
 ***********************************************/
template <class T>
void BST<T> ::remove(BSTIterator<T> & it)
{
   BinaryNode<T> * pRemove = it.getNode();
   BinaryNode<T> * pParent = pRemove->pParent;
   BinaryNode<T> * pNext;
   
   
   if(it != end())  // assume iterator is valid
   {

      //Node has 2 children
      if(pRemove->pLeft != NULL && pRemove->pRight != NULL)
      {
         //Find x's inorder successor and its parent
         pNext = pRemove->pRight;
         pParent = pRemove;
         while (pNext->pLeft != 0)      //descend left
         {
            pParent = pNext;
            pNext = pNext->pLeft;
         }
         
         //Move contents of next  to Remove and change Remove to apoint to Next, which will be remove
         pRemove->data = pNext->data;
         pRemove = pNext;
         
      } //end if node has 2 children
         

   
      //Node was 0 or 1 child
      pNext = pRemove->pLeft;          //pointer to next part of the tree

      if(pNext ==0)
         pNext = pRemove->pRight;

      if(pParent == NULL)                              //root being removed
         pRoot = pNext;
      else if(pParent->pLeft == pRemove)               //left child of parent
         pParent->pLeft = pNext;
      else
         pParent->pRight = pNext;                     //rigth child of parent

      delete pRemove;
   }
   
}


/************************************************
 * BSTIterator
 * Class iterator used for th BST
 ***********************************************/
template <class T>
class BSTIterator
{
   
private:
   stack < BinaryNode <T> * > nodes;
   
   
   
public:
   //Constructor
   BSTIterator(BinaryNode <T> * t = NULL) {nodes.push(t);}
   BSTIterator(stack < BinaryNode <T> * >s) : nodes(s) {}
   BSTIterator(const BSTIterator<T>& rhs):nodes(rhs.nodes){}
   
   //Operators
   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node
      return rhs.nodes.top() == nodes.top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node
      return rhs.nodes.top() != nodes.top();
   }
   
   T & operator*() throw(const char *)
   {
      return nodes.top()->data;
      
   }
   
   BSTIterator<T> & operator=(const BSTIterator<T> &rhs)
   {
      this->nodes = rhs.nodes;
      return *this;
   }
   

   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // Increment & Decrement operators
   BSTIterator<T> & operator -- ();
   BSTIterator<T> & operator--(int postfix);
   BSTIterator<T> & operator++();
   BSTIterator<T> & operator++(int postfix);


};

/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin()
{
   stack < BinaryNode <T> * > nodes;
   
   nodes.push(NULL);
   nodes.push(pRoot);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);
   
   return nodes;
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: rbegin()
{
   stack < BinaryNode <T> * > nodes;
   
   nodes.push(NULL);
   nodes.push(pRoot);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);
   
   return nodes;
}



/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);
      
      // there might be more right-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }
   
   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();
   
   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;
   
   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   
   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }
   
   return *this;


}


/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one. Note that this implementation uses
 *     a stack of nodes to remember where we are. This stack
 *     is called "nodes".
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}

#endif // BST_H

