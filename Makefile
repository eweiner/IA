


all:
	make clean
	g++ -c main.cpp boards.cpp agents.cpp
	g++ -o a.out main.o boards.o agents.o

clean: 
	rm -f *.o main a.out

debug:
	make clean
	g++ -g main.cpp boards.cpp agents.cpp