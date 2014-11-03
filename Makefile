all: rshell

FLAGS=-Wall -Werror -ansi -pedantic
CC=g++


rshell: 
	src/rshell.cpp
	@if[!-d bin/];\ 
	then\
	mkdir bin;\  
	fi
	$(CC) $(FLAGS) src/rshell.cpp -o bin/rshell

clean: 
	rm -rf  bin/*.o bin/rshell
	
