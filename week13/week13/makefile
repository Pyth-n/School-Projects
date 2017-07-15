###############################################################
# Program:
#     Week 13, Graph
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
# Summary:
#     Final week assignment Graph and maze
#
# Time:
#    Pair programming - 1
#	  Jeffry Simpson   - 4
#     David Perez     - 6
#
## Difficulties:
#    David - Tried to use the adjency-list at first, had many 
#     problems. Then tried the adjency-matrix, had problems 
#     allocating a 2d array. Also, got stuck with isEdge() and
#     index()
#
#    Jeffry - Getting the maze to work and bring back the path,
#            Could not get findpath to work corretly, tried Set and
#            matrix array both.   Finally used sample code to debug
#            found an issue with the sample code too, finally got
#            that version to work.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o graph.o maze.o
	g++ -o a.out week13.o graph.o maze.o -g
	tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
##############################################################
week13.o: graph.h vertex.h week13.cpp
	g++ -std=c++11 -c week13.cpp -g

graph.o: graph.h set.h vertex.h graph.cpp
	g++ -std=c++11 -c graph.cpp -g

maze.o: maze.cpp maze.h vertex.h graph.h
	g++ -std=c++11 -c maze.cpp -g
