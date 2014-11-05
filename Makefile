FLAGS=-Wall -Werror -ansi -pedantic
CC=g++

all: rshell

rshell: 
	[ -e ./bin ] || mkdir bin 
	$(CC) $(FLAGS) ./src/rshell.cpp -o ./bin/rshell
	

clean: 
	rm -rf bin/*.o bin
	
