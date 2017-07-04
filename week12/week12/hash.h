/***********************************************************************
 * Module:
 *    Week 12, Hash Table
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Hash Class
 ************************************************************************/

#ifndef HASH_H
#define HASH_H

Class Hash
{
   
   /*
    
    Constructor: Non-default constructor and the copy constructor. The non-default constructor takes the number of
                 buckets as a parameter. If there is insufficient memory to allocate a new buffer, then the following
                 exception is thrown:
         ERROR: Unable to allocate memory for the hash.
    
    Destructor: Delete all the elements in the Hash.
    
    operator=: Assignment operator. Copy one Hash into another. If there is insufficient memory to allocate a new 
               buffer, then the following exception is thrown:
               ERROR: Unable to allocate memory for the hash.

    empty(): Determines whether the current Hash is empty.
  
    size(): Returns the number of elements in the Hash.
 
    capacity(): Returns the number of buckets in the Hash.
 
    clear(): Clear the contents. This method takes no parameters and returns nothing.
  
    find(): The parameter is the value to be found. Returns true if the value is found, false otherwise.
   
    insert(): Places a new instance of a value in the Hash. The parameter is the item to be inserted; there is no return value.
  
    hash(): This is a pure virtual function taking an element as a parameter and returning an index into the underlying array.
 
    Your Hash class will need to be able to handle hash table collisions. You can do this any way you choose, 
     but perhaps the easiest is to perform chaining using a List or a BST in the hash table
    
    
    */
   
};


#endif /* hash_h */
