#This Makefile file builds my assignment 6 project
# @Name: Veer Waje
# @Class: CS3377.007
# @Date: 04/20/2024

run : TwoPipesTwoChildren
	./TwoPipesTwoChildren
build : TwoPipesTwoChildren.o
	g++ -o TwoPipesTwoChildren TwoPipesTwoChildren.o
compile : TwoPipesTwoChildren.cpp
	g++ -c TwoPipesTwoChildren.cpp
clean :
	rm TwoPipesTwoChildren.o TwoPipesTwoChildren
