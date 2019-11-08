###############################################################
# Program:
#     Week 02, STACK
#     Brother JonesL, CS235
# Author:
#     David Donovan, David Perez Jeffry Simpson
# Summary:
#     Create a class encapsulating the notion of a stack
# Time:
#     Pair programming - 1.5 hour
#	  Jeffry Simpson - 2 hours
#	  David Donavan  - 2 hours
#     David Perez    - 5 hours
#
#         Difficulties:
#                 David P - Figuring out how to work with
#                       exponent order of operations and also
#                       a solution to convert postfix to assembly
#
#                 Jeffry - Playing with my own version of Push
#                          and forgetting to allocate memory in the
#                          beginning when its NULL
#
#                 David D - Issues with getting the Push function to work
#                           worked with David P to get it finished.
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h week02.o infix.o 
	g++ -o a.out week02.o infix.o 
	tar -cf week02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week02.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
week02.o: stack.h infix.h week02.cpp
	g++ -c week02.cpp

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp

clean:
	rm *.o a.out
