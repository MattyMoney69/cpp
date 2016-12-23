testing :  directory.o funix.o main.o permission.o
	g++ -ansi -Wall -g -o testing -O2 -g directory.o funix.o main.o permission.o

directory.o : directory.cpp directory.h
	g++ -ansi -Wall -g -c -O2 -g directory.cpp

funix.o : funix.cpp directory.h funix.h directory.h
	g++ -ansi -Wall -g -c -O2 -g funix.cpp

main.o : main.cpp directory.h funix.h directory.h funix.h
	g++ -ansi -Wall -g -c -O2 -g main.cpp

permission.o : permission.cpp directory.h funix.h directory.h funix.h permission.h
	g++ -ansi -Wall -g -c -O2 -g permission.cpp

clean : 
	rm -f testing directory.o funix.o main.o permission.o