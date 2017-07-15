/**********************************************
 * Graph.cpp
 * Authors: Jeffry Simpson, David Perez
 * Info: Source code for graph.h
 *       Implements matrix adjency graph
 **********************************************/

#include <iostream>
#include "graph.h"
#include "queue.h"

/**********************************************
 * Non-Default Constructor
 **********************************************/
Graph::Graph(int num)
{
   this->table = new bool[num * num];
   this->items = num;
}

/**********************************************
 * clear() : Sets slots to false
 **********************************************/
void Graph::clear()
{
   for (int i = 0; i < items * items; i++)
   {
      table[i] = false;
   }
}

/**********************************************
 * isEdge() : returns matrix boolean slot
 **********************************************/
bool Graph::isEdge(const Vertex v1, const Vertex v2) const
{
   return table[index(v1, v2)];
}

/**********************************************
 * findEdges() : returns sets of edges
 **********************************************/
Set<Vertex> Graph::findEdges(const Vertex & vFrom) const
{
   Vertex vTo;
   Set <Vertex> s;

   for (int i = 0; i < items; i++)
   {
      vTo.set(i);
      
      if (isEdge(vFrom, vTo))
         s.insert(vTo);
   }
   return s;
}

/**********************************************
 * findPath() : finds shortest path
 **********************************************/
Vector<Vertex> Graph::findPath(const Vertex & vFrom, const Vertex & vTo)
{
   int distance = 0;
   int * distances = new int[items];
   Vertex * predecessor = new Vertex[items];

   for (int i = 0; i < items; i++)
      distances[i] = -1;
   distances[vFrom.index()] = distance;

   Queue<Vertex> toVisit;
   toVisit.push(vFrom);

   while (!toVisit.empty() && distances[vTo.index()] == -1)
   {
      Vertex v = toVisit.front();
      toVisit.pop();

      if (distances[v.index()] > distance)
         distance++;

      Set<Vertex> s(findEdges(v));

      for (SetConstIterator<Vertex> it = s.cbegin(); it != s.cend(); ++it)
      {
         if (distances[(*it).index()] == -1)
         {
            distances[(*it).index()] = distance + 1;
            predecessor[(*it).index()] = v;
            toVisit.push((*it));
         }
      }
      distance++;
   }

   Vector<Vertex> path(distance + 1);
   if (distances[vTo.index()] == -1)
   {
      std::cout << "No path found\n";
      return path;
   }

   path.push_back(vTo);

   for (int i = 1; i <= distance; i++)
   {
      path.push_back(predecessor[path[i - 1].index()]);
   }
   
   delete[] distances;
   delete[] predecessor;

   return path;
}

/**********************************************
 * Assignment Operator : used to copy the graph
 **********************************************/
Graph & Graph::operator=(const Graph &rhs) throw(const char *)
{
   if (rhs.items == 0)
      return *this;

   if (items != rhs.items)
   {
      if (table != NULL)
         delete[] table;

      try
      {
         this->table = new bool[rhs.items * rhs.items];
         this->items = rhs.items;
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: unable to allocate space for the graph";
      }
   }

   // Copy
   for (int i = 0; i < items * items; i++)
   {
      table[i] = rhs.table[i];
   }

   return *this;
}

/**********************************************
 * add() : used to set matrix slot as true
 **********************************************/
void Graph::add(const Vertex & vFrom, const Vertex & vTo)
{
   table[index(vFrom, vTo)] = true;
}

void Graph::add(const Vertex & vFrom, const Set<Vertex> & sTo)
{
   for (SetConstIterator<Vertex> it = sTo.cbegin(); it != sTo.cend(); ++it)
   {
      table[index(vFrom, *it)];
   }
}

/**********************************************
 * Used to index array slots in the matrix table
 **********************************************/
int Graph::index(Vertex v1, Vertex v2) const
{
   return v1.index() * items + v2.index();
}
