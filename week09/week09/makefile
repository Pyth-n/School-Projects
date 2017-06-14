###############################################################
# Program:
#     Week 09, Binary Search Tree
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
# Summary:
#     <put a description here>
#
# Time:
#    Pair programming - 1 hour
#	  Jeffry Simpson   - 4.5 hour
#     David Perez     - hours
#
## Difficulties:
#    David  -
#
#    Jeffry - Getting the iterators to work correctly with stack
#             reversing the code for the ++ from the --
#             Getting DeleteTree to work corretly and not give a
#             NULL pointer exception
#
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week09.o
	g++ -o a.out week09.o -g
	tar -cf week09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week09.o     : the driver program
##############################################################
#week09.o: bnode.h bst.h stack.h week09.cpp sortBinary.h
week09.o: bnode.h bst.h week09.cpp sortBinary.h
	g++ -std=c++11 -c week09.cpp -g

