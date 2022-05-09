Date: Date.o main.o
	gcc -o Date Date.o main.o

Date.o: Date.o Date.h
	gcc -c Date.cpp

main.o: main.o Date.h
	gcc -c main.cpp