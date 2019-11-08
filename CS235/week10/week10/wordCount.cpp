/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 # Authors:
 #     Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/


#include "wordCount.h" // for wordCount() prototype

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   
   Map <string, int> counts;
   string findWord, filename;

   
   //Get File name for input
   cout << "What is the filename to be counted? ";
   cin >> filename;
   
   //Create Tree from file
   readFromFile(counts,filename);
   
   //Look for word frequency
   cout << "What word whose frequency is to be found. Type ! when done\n";
   cout << "> ";
   cin >> findWord;
   
   while(findWord != "!")
   {
      cout <<"\t" << findWord << " : " << counts[findWord] << endl;
      cout << "> ";
      cin >> findWord;
   }
   
   
}


/************************************************
 * readFromFile
 * Get input from text file and put it into the map
 ***********************************************/

void readFromFile(Map <string, int> & counts, const string & fileName)
{
   string stringInput;              //Words from file
   int value;
   
   ifstream fin(fileName);          //Open file
   if (fin.fail())
   {
      cout << "Unable to open file " << fileName << endl;
      return;
   }
   
   while(!fin.eof())                //While not at End of File
   {
      fin >> stringInput;           //Get next work
      
      if (fin.eof())
      {
         return;
      }
      else if (fin.fail())
      {
         cout << "Error reading from file\n";
         return;
      }
      else
      {
         
         value = counts[stringInput];       //look for value  (0 means we added it)
         counts[stringInput] = value+1;     //increase the value by one
      }
      
   }
   
}

