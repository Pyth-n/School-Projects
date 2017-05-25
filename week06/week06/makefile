###############################################################
# Program:
#     Week 06, NODE
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
#
# Summary:
#     Implement a linked-list and use it to implement the Insertion Sort.
#
# Time:
#    Pair programming - 1 hr
#	  Jeffry Simpson   - 1.5 hr
#     David Perez     -
#
# Difficulties:
#    David  -
#
#    Jeffry -
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h week06.o 
	g++ -o a.out week06.o  -g
	tar -cf week06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week06.o      : the driver program
#      <anything else?>
##############################################################
week06.o: node.h week06.cpp sortInsertion.h
	g++ -std=c++11 -c week06.cpp -g

