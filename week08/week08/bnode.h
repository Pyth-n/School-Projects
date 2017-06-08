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
using namespace std;

#include <cassert>

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
   BinaryNode <T> * pLeft, *pRight, *pParent;
   
   
   BinaryNode() : data(), pLeft(NULL), pRight(NULL), pParent(NULL) {}
   BinaryNode(T t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL) {}
   BinaryNode(const BinaryNode<T> &rhs);
   
   //friend int sizeBtree(BinaryNode <T> * pAdd);
   
   int size();
   // Left data and nodes
   void addLeft (const T t) throw (const char *);
   void addLeft(BinaryNode<T> * left);
   // Add right data and nodes
   void addRight(const T t) throw (const char *);
   void addRight(BinaryNode<T> * right);
};
 
//outstream insertion operator
template <class T>
ostream & operator << (ostream & out, BinaryNode<T> * pNode)
{
   if (NULL != pNode)
   {
      out << pNode->pLeft << " " << pNode->pRight;
   }
   return out;
}

template<class T>
BinaryNode<T>::BinaryNode(const BinaryNode<T>& rhs) : pRight(NULL), pLeft(NULL), pParent(NULL)
{
   *this = rhs;
}

// Add data to node
template <class T>
void BinaryNode <T>::addLeft(const T t) throw (const char *)
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
}

// Add data to node
template <class T>
void BinaryNode<T>::addRight(const T t) throw(const char *)
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
}

template <class T>
BinaryNode <T> * copyBTree(const BinaryNode <T> * pSrc) throw (const char *)
{
   if (pSrc == NULL)
      return NULL;
   
   BinaryNode <T> * nDestination =  new BinaryNode <T>(pSrc->data);
   
   nDestination->pLeft =  copyBTree(pSrc->pLeft);
   
   if(nDestination->pLeft != NULL)
      nDestination->pLeft.pParent = nDestination;
      
      nDestination->pRight = copyBTree(pSrc->pRight);
      if(nDestination->pRight != NULL)
         nDestination->pRight.pParent = nDestination;
         
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
void deleteBinaryTree(BinaryNode <T> * & pNode)
{
   if(pNode == NULL)
      return;
   
   deleteBinaryTree(pNode->pLeft);
   deleteBinaryTree(pNode->pRight);
   delete pNode;
   
}





/*
 int sizeBTree(const BinaryNode <T> * node)
 {
 
 if(node == NULL)
 return 0;
 else
 return (sizeBTree(node->pLeft) + 1 + sizeBTree(node->pRight));
 }*/

#endif /* bnode_h */
