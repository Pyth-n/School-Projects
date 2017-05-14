###############################################################
# Program:
#     Week 05, SET
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
# Summary:
#     Implements a deque and is used to solve now serving problem
# Time:
#    Pair programming -
#	  Jeffry Simpson   -
#     David Perez     -
#
# Difficulties:
#    David  -
#    Jeffry -
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week05.o goFish.o card.o
	g++ -o a.out week05.o goFish.o card.o
	tar -cf week05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week05.o       : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
week05.o: set.h goFish.h week05.cpp
	g++ -std=c++11 -c week05.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -std=c++11 -c goFish.cpp

card.o: card.h card.cpp
	g++ -std=c++11 -c card.cpp 
