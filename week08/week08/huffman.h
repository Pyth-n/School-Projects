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
#include "queue.h"
#include "bnode.h"
#include "pair.h"

using namespace std;

typedef vector <pair <string,float >> vectPairNode;
typedef Pair <string, float> pairNode;


class Huffman
{
public:
   
   Huffman() { tree = NULL; }
 //  ~Huffman() { cout << "destructor\n"; deleteBinaryTree(tree); }
   
   Huffman(const pairNode & rhs) throw (bad_alloc)
   {
      tree = new BinaryNode < pairNode > (rhs);
   }
   
   Huffman(const string & first, float second) throw (bad_alloc)
   {
      pairNode pair(first, second);
      tree = new BinaryNode < pairNode > (pair);
     //tree = new BinaryNode < Pair <string, float> > (pair);
   }

   
   
   // add a sub-tree to our current tree
   void add(Huffman * pTree);
   void merge(Huffman tree);
   void Print() { cout << tree;}
   string Find(const string item);
   bool FindRecursive(const BinaryNode < Pair <string, float> > * pTree, const string item, string *result, string path = "" );
   
   // get the weight of the top-most element in the tree
   float getWeight() const  { return tree->data.second; }
   
   // extract the values from the tree
   void extract(const vectPairNode & input,
                Pair <string, string> output [])
   {
      extractRecursive(tree, string(""), input, output);
   }
   
private:
   // the recursive verson of extract
   void extractRecursive(BinaryNode < pairNode > * tree,
                         string sPrefix,
                         const vectPairNode & input,
                         Pair <string, string> output []);
   
   BinaryNode < pairNode > * tree;
};


void huffman(string fileName);
bool readFromFile(vectPairNode & huffmanQue, const string fileName);
bool readFromFile(vector <BinaryNode < Pair <string, float>>> & vectHuff, const string fileName);
bool readFromFile(vector <Huffman> & vectHuff, const string fileName);

#endif // HUFFMAN_h
