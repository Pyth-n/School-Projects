###############################################################
# Program:
#     Week 10, Map
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
# Summary:
#     Week 10 Map Assignment
#
# Time:
#    Pair programming - 1 hour
#	  Jeffry Simpson   - 3 hours
#     David Perez     - 4 hours
#
## Difficulties:
#    David - Getting the iterator to work and also finding a
#            way to dereference with the [] operator
#
#    Jeffry -  Getting the Balance function to work and setting the
#              red and black nodes in the right place
#
##############################################################
# The main rule
##############################################################
a.out: week10.o wordCount.o
	g++ -o a.out week10.o wordCount.o 
	tar -cf week10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week10.o       : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
week10.o: bnode.h bst.h pair.h map.h week10.cpp
	g++ -std=c++11 -c week10.cpp

wordCount.o: map.h wordCount.h wordCount.cpp bnode.h bst.h
	g++ -std=c++11 -c wordCount.cpp 
