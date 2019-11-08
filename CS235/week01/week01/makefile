###############################################################
# Program:
#     Week 01, Vector
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson
# Summary:
#     Week 01 Vector assignment
# Time:
#     Weeks and Weeks, and Years and Years and at least 16 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h week01.o
	g++ -o a.out week01.o 
	tar -cf week01.tar vector.h week01.cpp makefile

##############################################################
# The individual components
#      week01.o     : the driver program
##############################################################
week01.o: vector.h week01.cpp
	g++ -c week01.cpp
