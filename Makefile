FLAGS=-Wall -Werror -ansi -pedantic
CC=g++

all: rshell

rshell: src/rshell.cpp
	@if[! -d bin/];\
	then \
	mkdir bin; \
	fi
	$(CC)-c $(FLAGS) src/rshell.cpp -o bin/rshell

clean: rm bin/*.o bin/rshell
	
