FLAGS=-Wall -Werror -ansi -pedantic
CC=g++


all: cp rshell ls

cp: 
	[ -e ./bin ] || mkdir bin
	$(CC) $(FLAGS) ./src/cp.cpp -o ./bin/cp

rshell: 
	[ -e ./bin ] || mkdir bin 
	$(CC) $(FLAGS) ./src/rshell.cpp -o ./bin/rshell
	
ls: 
	[ -e ./bin ] || mkdir bin
	$(CC) $(FLAGS) ./src/ls.cpp -o ./bin/ls

clean: 
	rm -rf bin/*.o bin
	
