/***********************************************************************
 * Component:
 *    Week 13, Graph
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    the graph class
 ************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>
#include "list.h"
#include "queue.h"
#include "set.h"
#include "vector.h"
#include "vertex.h"

class Graph
{
   
private:
   bool **matrix;
   int items;
   
public:
   Graph(int grid) : items(grid)
   {

      matrix = new bool*[grid];
      
      for(int i = 0; i < grid; i++)
         matrix[i] = new bool[grid];
   }
   
   int size() const  { return items; }
   
   void add(Vertex v1, Vertex v2)
   {
      
   }
   
   void add(Vertex v1, Set <Vertex> s)
   {
      
   }

   void clear(){}

   
   bool isEdge(Vertex v1, Vertex v2) const
   {
      return false;
   }
   
   Set <Vertex> findEdges(Vertex v)
   {
      Set <Vertex> s;
      
      return s;
      
   }
   

};



#endif //GRAPH_H
