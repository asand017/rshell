#include <pwd.h>
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
#include <time.h>
#include <stdlib.h>

//#include "boost/format.hpp"

using namespace std;
//using boost::format;
//using boost::io::group;

//PRINTING OUT VECTOR OF FILES
void print_files(vector<string>& x) {
	for(unsigned i = 0; i < x.size(); ++i) {
		cout << x.at(i) << "  ";	
	}
	cout << endl;
	return;
}

void print_l(vector<string>& x) {
	struct stat club;
	int intake;
	struct passwd* move = getpwnam("root");
	if(!move) {
		cerr << "no root account" << endl;
		exit(1);
	}
	string cow;
	string now;
	ssize_t g = 0;
	for(unsigned i = 0; i < x.size(); ++i) {
		now = x[i];
		if(stat(now.c_str(), &club) == -1) {
			perror("stat");
			exit(1);
		}
		g += club.st_size;
	}
	cout << "total " << g << endl;	
	for(unsigned i = 0; i < x.size(); ++i) {
		cow = x[i];
		if(stat(cow.c_str(), &club) == -1) {
			perror("stat");
			exit(-1);
		}

		if(S_ISDIR(club.st_mode))
			cout << "d";
		else
			cout << "-";
		if((intake = access(cow.c_str(), R_OK)) == 0)
			cout << "r";
		else
			cout << "-";
		
		if((intake = access(cow.c_str(), W_OK)) == 0)
			cout << "w";
		else
			cout << "-";

		if((intake = access(cow.c_str(), X_OK)) == 0)
			cout << "x";
		else
			cout << "-";

		cout << "------" << " ";		


		cout << club.st_nlink << " ";
		cout << club.st_uid << " ";
		cout << club.st_gid << " ";
		cout << setw(5) << club.st_size << " ";
		cout << setw(5) << club.st_mtime << "sec ";			
		cout << left << setw(0) << x[i] << endl;
	}

}

//-a
void alphabetize2(vector<string>& x) {
	unsigned i;
	vector<string> ad;
	vector<string> qw;
	unsigned j;
	unsigned k;
	for(i = 0; i < x.size(); i++)
	{
		if(x[i][0] >= 65 && x[i][0] <= 90){
			x[i][0] += 32;
			qw.push_back(x[i]);	
		}
		
		if(x[i][0] == '.' && x[i][1] != '.'){
 			x[i].erase(0,1);
			ad.push_back(x[i]);	
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
		for(k = 0; k < ad.size(); k++)
		{
			if(ad[k] == x[i])
				x[i].insert(0, ".");
		
		}
	}	
}

//default alphabetize
void alphabetize(vector<string>& x) {
	unsigned i;
	vector<string> qw;
	unsigned j;
	for(i = 0; i < x.size(); i++)
	{
		if(x[i][0] >= 65 && x[i][0] <= 90){
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

//-a
static void lookup2()//const char *arg)
{
	vector<string> temp;
	DIR *start;
	struct dirent *entry;
//	char* x;
	if((start=opendir(".")) == NULL) {
		perror("opendir");
		return;
	}
	
	do {
		errno = 0;
		if((entry = readdir(start)) != NULL) {

//			x = entry->d_name;
			
			temp.push_back(entry->d_name);			
		}
		
	} while(entry != NULL);
	
	alphabetize2(temp);
	print_files(temp);	

	if(errno != 0)
		perror("error reading directory");	
	
	closedir(start);
	return;
}

//-l
static void lookup3()//const char *arg) 
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
	print_l(temp);

	if(errno != 0)
		cerr << errno << endl;
		//perror("error reading directory");	
	
	closedir(start);
	return;
}


//ls (passed in directory
static void lookup_d(char* q)//const char *arg) 
{
	vector<string> temp;
	DIR *start;
	struct dirent *entry;
	char* x;
	if((start=opendir(q)) == NULL) 
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

int main( int argc, char *argv[]) {
	string flag = "-a";
	string flag2 = "-l";
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
		return 0;
	}
	int i = 1;
	for(; i < argc; ++i) {	
		if(argv[i][0] != '-')
			lookup_d(argv[i]);
		
			
		
	}
	
	if(argv[1][0] != '-')
	{
		lookup_d(argv[1]);
	}
	else if(argv[1] == flag)
	{
		lookup2();	
	}
	else if(argv[1] == flag2)
	{
		lookup3();
	}
	return 0;
}
