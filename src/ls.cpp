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
#include <iomanip>
#include <vector>

using namespace std;
//PRINTING OUT VECTOR OF FILES
void print_files(vector<string>& x) {
	for(unsigned i = 0; i < x.size(); ++i) {
		cout << setw(10) << x.at(i);	
	}
	cout << endl;
	return;
}
//FOR NO FLAGS
static void lookup()//const char *arg)
{
	//cout.width(10);
	vector<string> temp;
	DIR *start;
	struct dirent *entry;
	
	if((start=opendir(".")) == NULL) {
		perror("opendir");
		return;
	}
	
	do {
		errno = 0;
		if((entry = readdir(start)) != NULL) {
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) 
				continue;
			temp.push_back(entry->d_name);
			//cout << setfill(' ') << setw(10) <<  entry->d_name;
			//printf(entry->d_name, 65);
			continue;
		}
		print_files(temp);
		//cout << endl;	
		//closedir(start);
		//	return;
		
	} while(entry != NULL);

	if(errno != 0)
		perror("error reading directory");
		//printf("failed to find %s\n", arg);
	
	closedir(start);
	return;
}
//FOR FLAGS
static void lookup2()//const char *arg)
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
			//if(strcmp(entry->d_name)//, arg) != 0) {
			cout << entry->d_name << setw(14);
			//printf(entry->d_name, 65);
			continue;
		}
		cout << endl;	
		//closedir(start);
		//	return;
		
	} while(entry != NULL);

	if(errno != 0)
		perror("error reading directory");
		//printf("failed to find %s\n", arg);
	
	closedir(start);
	return;
}


int main( int argc, char *argv[]) {
	string flag = "-a";
	string flag2 = "-l";
	string flag3 = "-R";
	string flag4 = "-aR";
	string flag5 = "-al";
	string flag6 = "-lR";
	string flag7 = "-Rl";
	string flag8 = "-Ra";
	string flag9 = "-la";	
	if(argc == 1)
		lookup();
	else if(argc == 2) {
		if(argv[1] == flag.c_str())
			lookup2();
	}
	

	return 0;
}
