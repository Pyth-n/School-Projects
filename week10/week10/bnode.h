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


// debug stuff
#ifndef debug
#ifdef DEBUG
#define debug(x) x
#else
#define debug(x)
#endif // DEBUG
#endif // !debug


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
   
   
   BinaryNode() : data(), pLeft(NULL), pRight(NULL), pParent(NULL), isRed(true) {}
   BinaryNode(const T t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL), isRed(true) {}
   BinaryNode(const BinaryNode<T> &rhs);
   
   
   //inline
   void setBlack()   { isRed == true;}
   void setRed()     { isRed == false;}
   //   bool isRed()      { return isRed;}
   
   int size() const
   {
      if(NULL == this )
         return 0;
      else
         return (this->pLeft->size() + 1 + this->pRight->size());
   }
   
   
   // Add Left and Right data and nodes
   void addLeft(BinaryNode<T> * left);
   void addRight(BinaryNode<T> * right);
   
   // Add Const Left & Right  data & nodes
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);
   
   // is the passed node our right child?
   bool isRightChild(BinaryNode <T> * pNode) const { return pRight == pNode; }
   bool isLeftChild( BinaryNode <T> * pNode) const { return pLeft  == pNode; }
   
   
   // balance the tree
   void balance();
   
#ifdef DEBUG
   // verify
   void verifyBTree() const;
   
   // how deep is the black nodes?
   int findDepth() const;
   
   // make sure all four red-black rules are followed
   void verifyRedBlack(int depth) const;
#endif // DEBUG
   
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
   assert(pLeft == NULL);
   assert(t <= data);
   try
   {
      // add the new node
      BinaryNode<T> * pNode = new BinaryNode <T> (t);
      addLeft(pNode);
      
      // paranoia and double-checks
      debug(verifyBTree());
      debug(std::cerr << "addLeft(" << t << ") ");
      
      pNode->balance();
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }
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
   assert(pRight == NULL);
   assert(t >= data);
   try
   {
      // add the new node
      BinaryNode<T> * pNode = new BinaryNode <T> (t);
      addRight(pNode);
      
      // paranoia and double-checks
      debug(verifyBTree());
      debug(std::cerr << "addRight(" << t << ") ");
      
      pNode->balance();
   }
   catch (...)
   {
      throw "ERROR: Unable to allocate a node";
   }
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


/******************************************************
 * BINARY NODE :: BALANCE
 * Balance the tree from a given location
 ******************************************************/
template <class T>
void BinaryNode <T> :: balance()
{
   debug(verifyBTree());
   
   // Case 1: if we are the root, then color ourselves black and call it a day.
   if (pParent == NULL)
   {
      isRed = false;
      debug(std::cerr << "Case 1\n");
      return;
   }
   
   // Case 2: if the parent is black, then there is nothing left to do
   if (pParent->isRed == false)
   {
      debug(std::cerr << "Case 2\n");
      return;
   }
   
   // we better have a grandparent.  Otherwise there is a red node at the root
   assert(pParent->pParent != NULL);
   
   // find my relatives
   BinaryNode <T> * pGranny  = pParent->pParent;
   BinaryNode <T> * pGreatG  = pGranny->pParent;
   BinaryNode <T> * pSibling =
   pParent->isRightChild(this   ) ? pParent->pLeft : pParent->pRight;
   BinaryNode <T> * pAunt    =
   pGranny->isRightChild(pParent) ? pGranny->pLeft : pGranny->pRight;
   
   // verify things are as they should be
   assert(pGranny != NULL);          // I should have a grandparent here
   assert(pGranny->isRed == false);  // if granny is red, we violate red-red!
   
   // Case 3: if the aunt is red, then just recolor
   if (pAunt != NULL && pAunt->isRed == true)
   {
      // verification
      debug(std::cerr << "Case 3, ");
      debug(pGranny->verifyBTree());
      
      // perform Case 3
      pGranny->isRed = true;         // grandparent becomes red
      pParent->isRed = false;        // parent becomes black
      pAunt->isRed  = false;         // aunt becomes black
      pGranny->balance();            // balance granny!
      return;
   }
   
   // Case 4: if the aunt is black or non-existant, then we need to rotate
   assert(pParent->isRed == true && pGranny->isRed == false &&
          (pAunt == NULL || pAunt->isRed == false));
   debug(pGranny->verifyBTree());
   
   // the new top of the sub-tree
   BinaryNode <T> * pHead = NULL;
   
   // Case 4a: We are mom's left and mom is granny's left
   if (pParent->pLeft == this && pGranny->pLeft == pParent)
   {
      // verify case 4a is as it should be
      debug(std::cerr << "Case 4a\n");
      debug(pGranny->verifyBTree());
      assert(pParent->pLeft == this);
      assert(pGranny->pRight == pAunt);
      assert(this->isRed == true);
      
      // perform the necessary rotation
      pGranny->addLeft(pSibling);
      pParent->addRight(pGranny);
      pHead = pParent;
      
      // set the colors
      pParent->isRed = false;
      pGranny->isRed = true;
   }
   
   // Case 4b: We are mom's right and mom is granny's left
   else if (pParent->pRight == this && pGranny->pLeft == pParent)
   {
      // verify case 4b is as it should be
      debug(std::cerr << "Case 4b\n");
      assert(pGranny->pRight == pAunt);
      assert(pParent->pLeft == pSibling);
      assert(pParent->isRed == true);
      
      // perform the necessary rotation
      pGranny->addLeft(this->pRight);
      pParent->addRight(this->pLeft);
      this->addLeft(pParent);
      this->addRight(pGranny);
      pHead = this;
      
      // set the colors
      this->isRed = false;
      pGranny->isRed = true;
   }
   
   // case 4c: We are mom's right and mom is granny's right
   else if (pParent->isRightChild(this) && pGranny->isRightChild(pParent))
   {
      // verify case 4c is as it should be
      debug(std::cerr << "Case 4c\n");
      assert(pParent->pRight == this);
      assert(pGranny->isRed == false);
      assert(pGranny->pLeft == pAunt);
      
      // perform the necessary rotation
      pParent->addLeft(pGranny);
      pGranny->addRight(pSibling);
      pHead = pParent;
      
      // set the colors
      pGranny->isRed = true;
      pParent->isRed = false;
   }
   
   // case 4d: we are mom's left and mom is granny's right
   else if (pParent->isLeftChild(this) && pGranny->isRightChild(pParent))
   {
      // verify case 4d is as it should be
      debug(std::cerr << "Case 4d\n");
      assert(pGranny->pLeft == pAunt);
      assert(pGranny->pRight == pParent);
      assert(pParent->pRight == pSibling);
      
      // perform the necessary rotation
      pGranny->addRight(this->pLeft);
      pParent->addLeft(this->pRight);
      this->addLeft(pGranny);
      this->addRight(pParent);
      pHead = this;
      
      // ste the colors
      this->isRed = false;
      pGranny->isRed = true;
      pParent->isRed = true;
   }
   
   // else we are really confused!
   else
   {
      assert(false); // !!
   }
   
   // fix up great granny if she is not null
   if (pGreatG == NULL)
      pHead->pParent = NULL;
   else if (pGreatG->pRight == pGranny)
      pGreatG->addRight(pHead);
   else if (pGreatG->pLeft == pGranny)
      pGreatG->addLeft(pHead);
   
   debug(pHead->verifyBTree());
}



// for week 10
// you might want to put these methods into your BinaryNode class
// to help you debug your red-black balancing code
#ifdef DEBUG
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
#endif // DEBUG


#endif /* bnode_h */
