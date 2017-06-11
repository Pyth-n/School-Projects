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
   bool fileFlag = true;
   int i, one, two;
   vectPairNode vHuffman, vPrint;
   vector <Huffman> vTree;

   
   //read the file into a data structure with the huffman class
   fileFlag = readFromFile(vTree, fileName);
   fileFlag = readFromFile(vHuffman, fileName);

   if(!fileFlag)
   {
      cout << "Error reading from file\n";
      return;
   }
   
   vPrint = vHuffman;  //Make a copy to be used later
   
   do
   {

      i = one = two =0;                      //set all the variables
      while(i < vHuffman.size())             //get the smallest two items
      {
         if(vHuffman[one].second > vHuffman[i].second )     //First the smallest
            one = i;
         i++;
      }
      
      i =0;
      if(one == 0)
         two = 1;
      
      while(i < vHuffman.size())                         //then the next smallest
      {
         if(vHuffman[two].second > vHuffman[i].second )
            if(one != i)
               two = i;
         i++;
      }

      
      if(vHuffman[two].first == "---")                 //symbolizes a place holder node from a created one
      {
         vTree[one].merge(vTree[two]);                //merge means its a tree, not a single node
      }
      else
      {
         Huffman huff1(vHuffman[two].first, vHuffman[two].second);      //create a new node to add
         vTree[one].add(&huff1);                                        //add the node to the tree
      }
      
      vHuffman[one].second += vHuffman[two].second;            //set new value
      vHuffman[one].first = "---";                             //ceate placeholder name value
      vTree.erase(vTree.begin() + two);                        //remove added node
      vHuffman.erase(vHuffman.begin() + two);                  //from both lists
   
      
   }while(vTree.size() > 1);                         //when we are down to one, everyone thing is in the tree

   //Print the output for Huffman Codes
   for(int x=0; x < vPrint.size(); x++)
      cout << vPrint[x].first << " = " << vTree[0].Find(vPrint[x].first) << endl;
   
   return;
}


/************************************************
 * Find
 * Find a value from the Tree
 ***********************************************/

string Huffman :: Find(const string item)
{
   string sResult="",sLeft = "0", sRight = "1";;
   bool flag = false;
   
   if(tree->data.first == item || (tree->pLeft == NULL && tree->pRight == NULL))
      return sResult;
   
   flag = FindRecursive(tree->pLeft, item, &sResult, sLeft);
   if(flag)
   {
      string temp = sLeft + sResult;
      sResult = temp;
      return sResult;
   };
   
   flag =  FindRecursive(tree->pRight, item, &sResult, sRight);
   if(flag)
   {
      string temp = sRight + sResult;
      sResult = temp;
      return sResult;
   }
   
   return sResult;
}

/************************************************
 * FindRecursive
 * Find a value from a Sub-Tree
 ***********************************************/
bool Huffman :: FindRecursive(const BinaryNode < Pair <string, float> > * pTree, const string item,string *sResult, string path)
{
   bool flag = false;
   string sLeft = "0", sRight = "1";
   
   if(pTree->data.first == item )
      return true;

   
   if(pTree->pLeft != NULL)
   {
      flag = FindRecursive(pTree->pLeft, item, sResult, sLeft);
   
      if(flag)
      {
         string temp = sLeft + *sResult;
         *sResult = temp;
         return flag;
      }
   }
   
   if(pTree->pRight != NULL)
   {
      flag = FindRecursive(pTree->pRight, item, sResult, sRight);
      if(flag)
      {
         string temp = sRight + *sResult;
         *sResult = temp;
         return flag;
      }
   }
   
   
   return flag;
}


/************************************************
 * add
 * add a sub tree to our existing tree
 ***********************************************/
void Huffman::add(Huffman * second)
{
   
   Huffman * newHuff = new Huffman(".",second->getWeight() + getWeight());
   Huffman * newSecond = new Huffman(second->tree->data.first,second->tree->data.second );
   
   if(second->getWeight() < getWeight())
   {
      newHuff->tree->addLeft(newSecond->tree);
      newHuff->tree->addRight(tree);
   }
   else
   {
      newHuff->tree->addLeft(tree);
      newHuff->tree->addRight(newSecond->tree);
      
   }
   
   *this = *newHuff;
   
}


/****************************************************
 * HUFFMAN :: merge
 * Merge one subtree (pTree) to the current Huffman Tree
 ***************************************************/
void Huffman :: merge(Huffman Tree)
{
   // allocate a new node, the parent
   BinaryNode < Pair <string, float> > * pNew =
   new BinaryNode < Pair <string, float> >;
   
   // the weight of the new node is the combination of the children's weight
   pNew->data.second = getWeight() + Tree.getWeight();
   
   // attach the left and right children to myself
   if (getWeight() <= Tree.getWeight())
   {
      pNew->pLeft  = tree;
      pNew->pRight = Tree.tree;
   }
   else
   {
      pNew->pLeft  = Tree.tree;
      pNew->pRight = tree;
   }
   
   // make the new tree the root and all
   tree = pNew;
}


/************************************************
 * readfromFile
 * Get input from text and put it in a Vector Pair object
 ***********************************************/
bool readFromFile(vectPairNode & huffmanQue, const string fileName)
{
   string stringInput;              //String from file
   float valueInput;               //double from file
   pair<string,float> curItem;
   
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
         curItem.first = cstr;
         curItem.second = valueInput;
         huffmanQue.push_back(curItem);                         //Insert string
         delete [] cstr;                                       //Delete Char variable
      }
      
   }
   
   
   return true;
}



/************************************************
 * readfromFile
 * Get input from text file and put it in Vector Huffman object
 
 ***********************************************/

bool readFromFile(vector <Huffman>  & vectHuff, const string fileName)
{
   string stringInput;              //String from file
   float valueInput;               //double from file
   
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
         vectHuff.push_back(Huffman(Pair < string , float >(cstr,valueInput)));
         
         delete [] cstr;                                       //Delete Char variable
      }
      
   }
   
   
   return true;
}


