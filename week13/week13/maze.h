/***********************************************************************
 * Component:
 *    Week 13, Maze
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    Draw and solve a maze
 ************************************************************************/

#ifndef MAZE_H
#define MAZE_H

#include "graph.h"
//#include "vector.h"
#include <vector>

using namespace std;

// solve the maze, the main program function
void solveMaze();

// read a maze in from a file
Graph readMaze(const char * fileName);

// display a maze on the screen
void drawMaze(const Graph & g, const vector <Vertex> & path);

#endif // MAZE_H
