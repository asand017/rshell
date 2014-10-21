#include <iostream>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;

int main(int argc, char** argv)
{
	if(argc == 0) {
		cout << "No argument." << endl;
		exit(1);
	}
	
	int pid = fork();
	if(pid == 0) {

	//	argv[0] = new char[6];
	//	strcpy(argv[0], "ls");
	//	argv[1] = new char[6];
	//	strcpy(argv[1], "-a");
	//	argv[2] = new char [6];
	//	strcpy(argv[2], "-l");
		cout << "before" << endl;
		int r = execvp(argv[1], argv);

		if(r == -1) {
			perror("execvp");
			exit(1);
		}

		cout << "after" << endl;
	}
	else {
		wait(NULL);
	}

	return 0;
}
