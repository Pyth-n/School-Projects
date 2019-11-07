###############################################################
# Program:
#     Week 04, DEQUE
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
# Summary:
#     Implements a deque and is used to solve now serving problem
# Time:
#    Pair programming - 1.0
#	  Jeffry Simpson - 4.0
#     David Perez    - 4.0
#
# Difficulties:
#    David P - Finding a way to reallocate the dynamic 
#                 array to pass test 3 in the test bed.
#
#
#   Jeffry -
#
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h week04.o nowServing.o
	g++ -o a.out week04.o nowServing.o
	tar -cf week04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week04.o       : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
week04.o: deque.h week04.cpp
	g++ -std=c++11 -c week04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -std=c++11 -c nowServing.cpp
