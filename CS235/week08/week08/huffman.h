/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>    // for CIN and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <fstream>
#include <string.h>
#include <vector>
#include "bnode.h"
#include "pair.h"

using namespace std;

typedef vector <pair <string,float >> vectPairNode;
typedef Pair <string, float> pairNode;


class Huffman
{
public:
   
   Huffman() { tree = NULL; }
   
   Huffman(const pairNode & rhs) throw (bad_alloc)
   {
      tree = new BinaryNode < pairNode > (rhs);
   }
   
   Huffman(const string & first, float second) throw (bad_alloc)
   {
      pairNode pair(first, second);
      tree = new BinaryNode < pairNode > (pair);
  
   }

   
   
   void add(Huffman * pTree);             // add a sub-tree to our current tree
   void merge(Huffman tree);              // merge an existing tree with current
   void Print() { cout << tree;}          //Bring out tree
   string Find(const string item);        //Find Name in tree
 
   
   // get the weight of the top-most element in the tree
   float getWeight() const  { return tree->data.second; }
   
   
private:
  bool FindRecursive(const BinaryNode < Pair <string, float> > * pTree,
                     const string item,
                     string *result,
                     string path = "" );
   
   BinaryNode < pairNode > * tree;
};


void huffman(string fileName);
bool readFromFile(vectPairNode & huffmanQue, const string fileName);
bool readFromFile(vector <Huffman> & vectHuff, const string fileName);

#endif // HUFFMAN_h
