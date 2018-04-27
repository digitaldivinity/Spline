spline.o : spline.cpp
	g++ -Wall -ansi -c spline.cpp
k_module.o: k_module.cpp
	g++ -Wall -ansi -c k_module.cpp
spline : spline.o k_module.o
	g++ -Wall -ansi spline.o k_module.o -o spline -lsfml-graphics -lsfml-window -lsfml-system
run: spline
	./spline
