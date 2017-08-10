main: main.o *.o util.o
	g++ -o main main.o *.o util.o

main.o: main.cpp
	g++ -c main.cpp

*.o: src/*.cpp 
	g++ -c src/*.cpp include/*.h

util.o: src/util/*.cpp 
	g++ -c src/util/*.cpp include/util/*.h