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
   bool getRed()     { return isRed;}
   
   int size();
   
   // Left data and nodes
   void addLeft (const T & t) throw (const char *);
   void addLeft(BinaryNode<T> * left);
   // Add right data and nodes
   void addRight(const T & t) throw (const char *);
   void addRight(BinaryNode<T> * right);
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





/*
 int sizeBTree(const BinaryNode <T> * node)
 {
 
 if(node == NULL)
 return 0;
 else
 return (sizeBTree(node->pLeft) + 1 + sizeBTree(node->pRight));
 }*/

#endif /* bnode_h */
