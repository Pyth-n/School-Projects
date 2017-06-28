###############################################################
# Program:
#     Week 11, Sorts
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
# Summary:
#     Week 11 Sorting
# Time:
#    Pair programming -  hour
#	  Jeffry Simpson   -  2 hours
#     David Perez     -  hours
#
## Difficulties:
#    David -
#
#
#    Jeffry -
#
#
##############################################################

##############################################################
# The main rule
##############################################################
a.out: week11.o
	g++ -o a.out week11.o -g
	tar -cf week11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week11.o     : the driver program
##############################################################
week11.o: bnode.h bst.h week11.cpp sortValue.h \
		sortBinary.h sortInsertion.h sortHeap.h sortBubble.h \
		sortSelection.h sortMerge.h sortQuick.h
	g++ -std=c++11 -c week11.cpp -g

