/***********************************************************************
* Header:
*    WORD COUNT
* Summary:
*    This will contain just the prototype for the wordCount()
*    function
* Author
*    <your names here>
************************************************************************/

#ifndef WORD_COUNT_H
#define WORD_COUNT_H

#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <fstream>
#include "map.h"       // for MAP

using namespace std;

//Function definitions
void readFromFile(Map <string, int> & counts, const string & fileName);
void wordCount();

#endif // WORD_COUNT_H

