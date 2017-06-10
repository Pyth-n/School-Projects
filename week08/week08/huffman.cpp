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
   vectPairNode vHuffman;
   bool fileFlag = true;
   int i, one, two;
   float sum;
   //vector <BinaryNode < Pair <string, float>>> vectHuff;
   vector <Huffman> vTree;

   
   cout << "Start Huffman function\n";
   
   //Create a huffman class using the pair.h
 //  fileFlag = readFromFile(vectHuff, fileName);
   fileFlag = readFromFile(vTree, fileName);
   //read the file into a data structure with the huffman class
   fileFlag = readFromFile(vHuffman, fileName);

   if(!fileFlag)
   {
      cout << "Error reading from file\n";
      return;
   }
   
   
   do
   {
      if(vHuffman.size() > 1)
      {

         i = one = two =0;
         while(i < vHuffman.size())
         {
            if(vHuffman[one].second > vHuffman[i].second )
               one = i;
            i++;
         }
         
         i =0;
         if(one == 0)
            two = 1;
         
         while(i < vHuffman.size())
         {
            if(vHuffman[two].second > vHuffman[i].second )
               if(one != i)
                  two = i;
            i++;
         }

         cout << vHuffman[one].first << " - "<< vHuffman[one].second << endl;
         cout << vHuffman[two].first << " - "<< vHuffman[two].second << endl;
         
       
         
         Huffman huff1(vHuffman[two].first, vHuffman[two].second);
         vTree[one].add(&huff1);
         
         vHuffman[one].second += vHuffman[two].second;
         vHuffman[one].first = "---";
         vTree.erase(vTree.begin() + two);
         vHuffman.erase(vHuffman.begin() + two);
         
      }
      else
      {
         //do something with the last node.
      }
      

      
   }while(vTree.size() > 1);

 //  Huffman  huff1(vHuffman[0].first, vHuffman[0].second);
//   Huffman huff2(vHuffman[1].first, vHuffman[1].second);
   
 //  pairNode trial(vHuffman[2].first, vHuffman[2].second);
 //  Huffman  huff(trial);
   
 //  vectHuff.push_back(huff1);
//   vectHuff.push_back(huff);
   cout << "Before first huff.add()\n";
   
 //  huff.add(&huff1);
   
   
//   cout << huff.getWeight();
   
      cout << "Before second huff add()\n";
   
//   huff.add(&huff2);
 //  vectHuff.push_back(huff1);
   
   
 /*
   do
   {
      node first, second
  
      first = linkedlist.head
      if(linkedlist.seccond < first)
            second = first
            first = linkedlist.second
      else
         second = linklist.second
  
  while(ptail != NULL)
  {
    if(linkedList.next < second)
      if(linkedList.next < first)
          second = first
          first = linkedList.next
      else
         first = second
         second = linkedlist.next
  
  
  }

  Create a new node with p-left = first and p-right =second.
   newnode.prev = first.prev
   newnode.next = first.next 
  
  remove second node from the linked list
   second-prev-next = second-next 
   second-next-prev = second-prev
  
   delete(first)
   delete (second)
  
      
   }while(head != Tail)
   
   */
   
   
   //parse the structure, and create a tree with smallest two items
   
   //get the paths from the tree
   
   //display the path info
   cout << "End of Function\n";
   

  // huff.Delete();
  // huff1.Delete();
  // huff2.Delete();
   
   return;
}

/************************************************
 * add
 * Get input from text file
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
 * HUFFMAN :: ADD
 * Add the subtree (pTree) to the current Huffman Tree
 ***************************************************
void Huffman :: add(Huffman * pTree)
{
   // allocate a new node, the parent
   BinaryNode < Pair <string, float> > * pNew =
   new BinaryNode < Pair <string, float> >;
   
   // the weight of the new node is the combination of the children's weight
   pNew->data.second = getWeight() + pTree->getWeight();
   
   // attach the left and right children to myself
   if (getWeight() <= pTree->getWeight())
   {
      pNew->pLeft  = tree;
      pNew->pRight = pTree->tree;
   }
   else
   {
      pNew->pLeft  = pTree->tree;
      pNew->pRight = tree;
   }
   
   // make the new tree the root and all
   tree = pNew;
}
*/

/************************************************
 * readfromFile
 * Get input from text file
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
 * Get input from text file
 
 ***********************************************/

bool readFromFile(vector <BinaryNode < Pair <string, float>>>  & vectHuff, const string fileName)
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
         // Huffman newItem(cstr,valueInput);
         //  Huffman * newHuff = new Huffman(".",second->getWeight() + getWeight());
         vectHuff.push_back(BinaryNode < Pair < string, float > >(Pair < string , float >(cstr,valueInput)));
         //vectHuff.push_back(newItem);                         //Insert string
         delete [] cstr;                                       //Delete Char variable
      }
      
   }
   
   
   return true;
}



/************************************************
 * readfromFile
 * Get input from text file
 
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
        // Huffman newItem(cstr,valueInput);
         //  Huffman * newHuff = new Huffman(".",second->getWeight() + getWeight());
         //vectHuff.push_back(BinaryNode < Pair < string, float > >(Pair < string , float >(cstr,valueInput)));
         vectHuff.push_back(Huffman(Pair < string , float >(cstr,valueInput)));
         //vectHuff.push_back(newItem);                         //Insert string
         delete [] cstr;                                       //Delete Char variable
      }
      
   }
   
   
   return true;
}


