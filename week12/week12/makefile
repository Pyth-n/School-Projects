###############################################################
# Program:
#     Week 12, Hash
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
# Summary:
#     <put a description here>
# Time:
#    Pair programming - 1
#	  Jeffry Simpson   -
#     David Perez     - 4
#
## Difficulties:
#    David - Understanding the pure virtual hash function and also 
#            how to write the insert()
#
#
#    Jeffry -
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week12.o spellCheck.o
	g++ -o a.out week12.o spellCheck.o -g
	tar -cf week12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week12.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
week12.o: hash.h week12.cpp list.h
	g++ -std=c++11 -c week12.cpp -g

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -std=c++11 -c spellCheck.cpp -g

