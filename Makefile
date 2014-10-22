opt = "-Wall -Werror -ansi -pedantic"
compiler = "g++"

all:
	mkdir bin
	g++ -c -Wall -Werror -ansi -pedantic rshell.cpp -o bin/rshell
	cd bin
	rshell
	rm -rf bin

rshell:
	mkdir bin 
	g++ -c -Wall -Werror -ansi -pedantic rshell.cpp -o bin/rshell
	cd bin 
	rshell
	rm -rf bin
	
