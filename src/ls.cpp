#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <errno.h>

using namespace std;

static void lookup(const char *arg)
{
	DIR *start;
	struct dirent *entry;
	
	if((start=opendir(".")) == NULL) {
		perror("opendir");
		return;
	}
	
	do {
		errno = 0;
		if((entry = readdir(start)) != NULL) {
			if(strcmp(entry->d_name, arg) != 0)
				continue;
		closedir(start);
			return;
		}
	} while(entry != NULL);

	if(errno != 0)
		perror("error reading directory");
	else
		printf("failed to find %s\n", arg);
	
	closedir(start);
	return;
}

int main(int argc, char *argv[]) {
	int i;
	for(i = 1; i <argc; i++)
		lookup(argv[i]);
	return 0;
}
