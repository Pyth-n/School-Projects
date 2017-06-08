/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/


#include "huffman.h"       // for HUFFMAN() prototype


/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(string fileName)
{
   Queue<HuffHolder> huffmanQue;
   HuffHolder item;
   bool flag = true;
   
   
   //Create a huffman class using the pair.h
   
   //read the file into a data structure with the huffman class
   flag = readFromFile(huffmanQue, fileName);
   if(!flag)
   {
      cout << "Error reading from file\n";
      return;
   }
   
   
   //parse the structure, and create a tree with smallest two items
   
   //get the paths from the tree
   
   //display the path info
   
   return;
}


/************************************************
 * readfromFile
 * Get input from text file
 ***********************************************/
bool readFromFile(Queue<HuffHolder> & huffmanQue, const string fileName)
{
   char * nextCard = nullptr;       //NextCard input
   string stringInput;              //String from file
   double valueInput;               //double from file
   HuffHolder curItem;
   
   ifstream fin(fileName);          //Open file
   if (fin.fail())
   {
      cout << "Unable to open file " << fileName << endl;
      return false;
   }
   
   while(!fin.eof())                //While not at End of File
   {
      fin >> stringInput;
      fin >> valueInput;
      
      if (fin.eof())
      {
         return true;
      }
      else if (fin.fail())
      {
         cout << "Error reading from file\n";
         return false;
      }
      else
      {
         
         char *cstr = new char[stringInput.length() + 1];      //Create Char variable
         strcpy(cstr, stringInput.c_str());                    //String copy
         curItem.name = cstr;
         //curItem.value = stod(valueInput);
         curItem.value = valueInput;
         huffmanQue.push(curItem);                                    //Insert string
         delete [] cstr;                                       //Delete Char variable
      }
      
   }
   
   
   return true;
}
