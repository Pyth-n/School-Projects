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
#include "queue.h"

using namespace std;

struct HuffHolder
{
   string name = "", huffcode = "";
   double value = 0.0;
};

BinaryNode <Pair<T1, T2>> hTree;

void huffman(string fileName);
bool readFromFile(Queue<HuffHolder> & huffmanQue, const string fileName);


#endif // HUFFMAN_h
