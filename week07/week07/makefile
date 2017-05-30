###############################################################
# Program:
#     Week 07, LIST
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
#
# Summary:
#    Create a class encapsulating the notion of a list.
#
# Time:
#    Pair programming -
#	  Jeffry Simpson   -
#     David Perez     -
#
# Difficulties:
#    David  -
#
#    Jeffry -
#
#
###############################################################


##############################################################
# The main rule
##############################################################
a.out: list.h week07.o fibonacci.o
	g++ -o a.out week07.o fibonacci.o
	tar -cf week07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week07.o       : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      <anything else?>
##############################################################
week07.o: list.h week07.cpp
	g++ -std=c++11 -c week07.cpp

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -std=c++11 -c fibonacci.cpp

