spline.o : spline.cpp
	g++ -Wall -ansi -c spline.cpp
spline : spline.o 
	g++ spline.o -o spline -lsfml-graphics -lsfml-window -lsfml-system
run: spline
	./spline<test
