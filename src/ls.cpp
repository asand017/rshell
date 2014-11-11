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
#include <algorithm>

using namespace std;
//PRINTING OUT VECTOR OF FILES
void print_files(vector<string>& x) {
	for(unsigned i = 0; i < x.size(); ++i) {
		cout << x.at(i) << "     ";	
	}
	cout << endl;
	return;
}

void alphabetize(vector<string>& x) {
	unsigned i;
	vector<string> qw;
	unsigned j;
	for(i = 0; i < x.size(); i++)
	{
		if(x[i][0] > 65 && x[i][0] < 90){
			x[i][0] += 32;
			qw.push_back(x[i]);
		}
	}
	sort(x.begin(), x.end());
	for(i = 0; i < x.size(); i++)
	{
		for(j = 0; j < qw.size(); j++)
		{
			if(qw[j] == x[i])
				x[i][0] -= 32;	
		}
	}	
}

//default
static void lookup()//const char *arg) //ls (no flags)
{
	vector<string> temp;
	DIR *start;
	struct dirent *entry;
	char* x;
	if((start=opendir(".")) == NULL) 
	{
		perror("opendir");
		return;
	}
	
	do {
		errno = 0;
		if((entry = readdir(start)) != NULL) 
		{	
			x = entry->d_name;						

			if(x[0] == '.') 
				continue;
					
			temp.push_back(entry->d_name);
		}	
		
	} while(entry != NULL);
	
	alphabetize(temp);
	print_files(temp);

	if(errno != 0)
		perror("error reading directory");	
	
	closedir(start);
	return;
}
/*
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
*/

int main( int argc, char *argv[]) {
//	string flag = "-a";
//	string flag2 = "-l";
//	string flag3 = "-R";
//	string flag4 = "-aR";
//	string flag5 = "-al";
//	string flag6 = "-lR";
//	string flag7 = "-Rl";
//	string flag8 = "-Ra";
//	string flag9 = "-la";	
	if(argc == 1)
	{	
		lookup();
	}
	
	return 0;
}
