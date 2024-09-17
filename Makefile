#This Makefile file builds my assignment 6 project
# @Name: Veer Waje
# @Class: CS3377.007
# @Date: 04/20/2024

twopipes_twochildren : TwoPipesTwoChildren
	./TwoPipesTwoChildren
build2 : TwoPipesTwoChildren.o
	g++ -o TwoPipesTwoChildren TwoPipesTwoChildren.o
compile2 : TwoPipesTwoChildren.cpp
	g++ -c TwoPipesTwoChildren.cpp
build3 : TwoPipesThreeChildren.o
	g++ -o TwoPipesThreeChildren TwoPipesThreeChildren.o
compile3 : TwoPipesThreeChildren.cpp
	g++ -c TwoPipesThreeChildren.cpp
twopipes_threechildren : TwoPipesThreeChildren
	./TwoPipesThreeChildren
clean :
	rm TwoPipesTwoChildren.o TwoPipesTwoChildren TwoPipesThreeChildren TwoPipesThreeChildren.0
