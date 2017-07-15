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
//#include "vector.h"
#include "vertex.h"

using namespace std;

class Graph
{
   
private:
   bool *table;
   int items;
   
public:

   Graph(int num);
   void clear();
   Set<Vertex> findEdges(const Vertex & vFrom) const;
   vector<Vertex> findPath(const Vertex & vFrom, const Vertex & vTo);
   bool isEdge(Vertex v1, Vertex v2) const;

   Graph & operator = (const Graph &rhs) throw (const char *);

   void add(const Vertex & vFrom, const Vertex & vTo);
   void add(const Vertex & vFrom, const Set<Vertex> & sTo);

   int index(Vertex v1, Vertex v2) const;
   int size() const { return items; }

};

#endif //GRAPH_H
