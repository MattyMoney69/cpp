songs.out : song.o main.o
	g++ -ansi -Wall -g -o songs.out song.o main.o

song.o : song.cpp song.h
	g++ -ansi -Wall -g -c song.cpp

main.o : main.cpp song.h
	g++ -ansi -Wall -g -c main.cpp

clean :
	rm -f songs.out song.o main.o
