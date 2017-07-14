#include <iostream>
#include "graph.h"
#include "queue.h"

Graph::Graph(int num)
{
   this->table = new bool[num * num];
   this->items = num;
}

void Graph::clear()
{
   for (int i = 0; i < items * items; i++)
   {
      table[i] = false;
   }
}

bool Graph::isEdge(Vertex v1, Vertex v2) const
{
   //return table[v1].find(v2) != NULL;

   return table[v1.index() * v2.index()];
}

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
   if (distances[vTo.index()] == -1);
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

const int Graph::index(Vertex v1, Vertex v2)
{
   return v1.index() * v2.index();
}
