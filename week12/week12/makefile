###############################################################
# Program:
#     Week 12, Hash
#     Brother JonesL, CS235
# Author:
#     Jeffry Simpson, David Perez
# Summary:
#     Hash table assignment for week 12
# Time:
#    Pair programming - 1
#	  Jeffry Simpson   - 4
#     David Perez     - 4
#
## Difficulties:
#    David - Understanding the pure virtual hash function and also 
#            how to write the insert()
#
#
#    Jeffry - Getting the virtual Hash to work with my derived class for
#             string hash.   Tried creating with varous hash functions and
#             finally went back to the first one I tried which was just summing
#             up the values of the ascii characters in the string.
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

