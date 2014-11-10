FLAGS=-Wall -Werror -ansi -pedantic
CC=g++

all: rshell ls

rshell: 
	[ -e ./bin ] || mkdir bin 
	$(CC) $(FLAGS) ./src/rshell.cpp -o ./bin/rshell
	
ls: 
	[ -e ./bin ] || mkdir bin
	$(CC) $(FLAGS) ./src/rshell.cpp -o ./bin/ls

clean: 
	rm -rf bin/*.o bin
	
