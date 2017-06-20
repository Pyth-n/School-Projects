/***********************************************************************
 * Header:
 *    bnode.h
 * Summary:
 *    This will contain the code for our week08 Binary Tree assignment
 * Author
 *    Jeffry Simpson, David Perez
 ************************************************************************/

#ifndef bnode_h
#define bnode_h
#include <iostream>
#include <cassert>

using namespace std;


/************************************************
 * Node
 * Basic class Node
 ***********************************************/
template <class T>
class BinaryNode
{
public:
   // Member variables
   T data;
   BinaryNode <T> *pLeft, *pRight, *pParent;
   bool isRed;
   
   
   BinaryNode() : data(), pLeft(NULL), pRight(NULL), pParent(NULL), isRed(false) {}
   BinaryNode(T t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL), isRed(false) {}
   BinaryNode(const BinaryNode<T> &rhs);
   
   
   //inline
   void setBlack()   { isRed == true;}
   void setRed()     { isRed == false;}
   bool isRed()      { return isRed;}
   
   int size();
   
   // Left data and nodes
   void addLeft (const T & t) throw (const char *);
   void addLeft(BinaryNode<T> * left);
   // Add right data and nodes
   void addRight(const T & t) throw (const char *);
   void addRight(BinaryNode<T> * right);

   //Extra methods for week 10
   int findDepth() const;
   void verifyRedBlack(int depth) const;
   void verifyBTree() const;

};
 
//outstream insertion operator
template <class T>
ostream & operator << (ostream & out, BinaryNode<T> * pNode)
{
   if (NULL != pNode)
   {
      cout << pNode->pLeft;
      out << pNode->data << " ";
      cout << pNode->pRight;
   }
   return out;
}

template<class T>
BinaryNode<T>::BinaryNode(const BinaryNode<T>& rhs) : pRight(NULL), pLeft(NULL), pParent(NULL), isRed(false)
{
   *this = rhs;
}

// Add data to node
template <class T>
void BinaryNode <T>::addLeft(const T & t) throw (const char *)
{
   if (!t)
      return;
   BinaryNode <T> * pAdd = new BinaryNode <T>(t);
   pAdd->pParent = this;
   pLeft = pAdd;
}

// Add a node to a node
template <class T>
void BinaryNode<T>::addLeft(BinaryNode<T> * left)
{
   pLeft = left;

   // NULL check, set parents
   if (NULL != left)
      pLeft->pParent = this;
   
}

// Add data to node
template <class T>
void BinaryNode<T>::addRight(const T & t) throw(const char *)
{
   if (!t)
      return;
   BinaryNode <T> * pAdd = new BinaryNode<T>(t);
   pAdd->pParent = this;
   pRight = pAdd;
}

template <class T>
void BinaryNode<T>::addRight(BinaryNode<T> * right)
{
   pRight = right;

   // NULL Check, set parents
   if (NULL != right)
      pRight->pParent = this;
}


template <class T>
BinaryNode <T> * copyBTree(const BinaryNode <T> * pSrc) throw (const char *)
{
   if (pSrc == NULL)
      return NULL;
   
   BinaryNode <T> * nDestination =  new BinaryNode <T>(pSrc->data);
   
   nDestination->pLeft =  copyBTree(pSrc->pLeft);
   
   if(nDestination->pLeft != NULL)
      nDestination->pLeft->pParent = nDestination;
      
      nDestination->pRight = copyBTree(pSrc->pRight);
      if(nDestination->pRight != NULL)
         nDestination->pRight->pParent = nDestination;
         
         return nDestination;
}


template <class T>
int BinaryNode <T>::size()
{
   
   if(NULL == this )
      return 0;
   else
      return (this->pLeft->size() + 1 + this->pRight->size());
}

template <class T>
void deleteBinaryTree(BinaryNode <T> *  pNode)
{
   if(pNode == NULL)
      return;
   if (pNode->pLeft != NULL)
      deleteBinaryTree(pNode->pLeft);
   if (pNode->pRight != NULL)
      deleteBinaryTree(pNode->pRight);
   delete pNode;
   
}

// for week 10
// you might want to put these methods into your BinaryNode class
// to help you debug your red-black balancing code

/****************************************************
 * BINARY NODE :: FIND DEPTH
 * Find the depth of the black nodes. This is useful for
 * verifying that a given red-black tree is valid
 * Author: Br. Helfrich
 ****************************************************/
template <class T>
int BinaryNode <T> :: findDepth() const
{
   // if there are no children, the depth is ourselves
   if (pRight == NULL && pLeft == NULL)
      return (isRed ? 0 : 1);
   
   // if there is a right child, go that way
   if (pRight != NULL)
      return (isRed ? 0 : 1) + pRight->findDepth();
   else
      return (isRed ? 0 : 1) + pLeft->findDepth();
}

/****************************************************
 * BINARY NODE :: VERIFY RED BLACK
 * Do all four red-black rules work here?
 * Author: Br. Helfrich
 ***************************************************/
template <class T>
void BinaryNode <T> :: verifyRedBlack(int depth) const
{
   depth -= (isRed == false) ? 1 : 0;
   
   // Rule a) Every node is either red or black
   assert(isRed == true || isRed == false); // this feels silly
   
   // Rule b) The root is black
   if (pParent == NULL)
      assert(isRed == false);
   
   // Rule c) Red nodes have black children
   if (isRed == true)
   {
      if (pLeft != NULL)
         assert(pLeft->isRed == false);
      if (pRight != NULL)
         assert(pRight->isRed == false);
   }
   
   // Rule d) Every path from a leaf to the root has the same # of black nodes
   if (pLeft == NULL && pRight && NULL)
      assert(depth == 0);
   if (pLeft != NULL)
      pLeft->verifyRedBlack(depth);
   if (pRight != NULL)
      pRight->verifyRedBlack(depth);
}

/******************************************************
 * VERIFY B TREE
 * Verify that the tree is correctly formed
 * Author: Br. Helfrich
 ******************************************************/
template <class T>
void BinaryNode <T> :: verifyBTree() const
{
   // check parent
   if (pParent)
      assert(pParent->pLeft == this || pParent->pRight == this);
   
   // check left
   if (pLeft)
   {
      assert(pLeft->data <= data);
      assert(pLeft->pParent == this);
      pLeft->verifyBTree();
   }
   
   // check right
   if (pRight)
   {
      assert(pRight->data >= data);
      assert(pRight->pParent == this);
      pRight->verifyBTree();
   }
}

#endif /* bnode_h */
