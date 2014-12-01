#include <sstream>
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
#include <fcntl.h>

using namespace std;

//PRINTING OUT VECTOR OF FILES
void print_files(vector<string>& x) {
	unsigned z = 0;
	for(unsigned i = 0; i < x.size(); ++i) {
		if(z == 5)
			cout << endl;
		cout << setw(16) << left << x.at(i) << "  ";
			++z;
	}
	cout << endl;
	return;
}

void print_l(vector<string>& x) {
	struct stat club;
	int intake;	
	string cow;
	string now;
	ssize_t g = 0;
	for(unsigned i = 0; i < x.size(); ++i) {
		now = x[i];
	//	int fd = open(now.c_str(), O_RDONLY);
	//	if(fd == -1)
	//	{
	//		perror("open");
	//		exit(1);
	//	}
		if(stat(now.c_str(), &club) == -1) {
			perror("stat");
			exit(1);
		}
		g += club.st_size;
	//	int fo = close(fd);
	//	if(fo == -1)
	//	{
	//		perror("close");
	//		exit(1);
	//	}
	
	}
	cout << "total " << g << endl;	
	for(unsigned e = 0; e < x.size(); ++e) {
		cow = x[e];
	//	int fd = open(now.c_str(), O_RDONLY);
	//	if(fd == -1)
	//	{
	//		perror("open");
	//		exit(1);
	//	}

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
		cout << left << setw(0) << x[e] << endl;
	//	int fo = close(fd);
	//	if(fo == -1)
	//	{
	//		perror("close");
	//		exit(1);
	//	}
	

	}

	return;

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
static void lookup()//ls (no flags)
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
	
	if(-1 == closedir(start))
	{
		perror("closedir");
	}
	return;
}

//-a
static void lookup2()
{
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
			temp.push_back(entry->d_name);			
		}
		
	} while(entry != NULL);
	
	alphabetize2(temp);
	print_files(temp);	

	if(errno != 0)
		perror("error reading directory");	
	
	if(-1 == closedir(start))
	{
		perror("closedir");
	}
	return;
}



//-la
static void lookup31()
{
	vector<string> temp;
	DIR *start;
	struct dirent *entry;

	if((start=opendir(".")) == NULL) 
	{
		perror("opendir");
		return;
	}
	
	do {
		errno = 0;
		if((entry = readdir(start)) != NULL) 
		{	
			temp.push_back(entry->d_name);
		}
			
		
	} while(entry != NULL);
	
	alphabetize(temp);
	print_l(temp);

	if(errno != 0)
		perror("error reading directory");	
	
	if(-1 == closedir(start))
	{
		perror("closedir");
	}
	return;
}


//-l
static void lookup3()
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

	if(errno != 0){	

		perror("error reading directory");	
	}

	if(-1 == closedir(start))
	{
		perror("closedir");
	}
	return;
}


static void lookup_d1(char* q)
{
	vector<string> temp;
	DIR *start;
	struct dirent *entry;
	if((start=opendir(q)) == NULL) 
	{
		perror("opendir");
		return;
	}
	
	do {
		errno = 0;
		if((entry = readdir(start)) != NULL) 
		{		
			temp.push_back(entry->d_name);
		}	
		
	} while(entry != NULL);
	
	alphabetize(temp);
	print_files(temp);

	if(errno != 0)
		perror("error reading directory");	
	
	if(-1 == closedir(start))
	{
		perror("closedir");
	}
	return;
}

//-lR
static void dlookup_d(char* q)
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
	print_l(temp);

	if(errno != 0)
		perror("error reading directory");	
	
	if(-1 == closedir(start))
	{
		perror("closedir");
	}
	return;
}


//ls (passed in directory
static void lookup_d(char* q)
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
	
	if(-1 == closedir(start))
	{
		perror("closedir");	
	}
	return;
}


//-Ra
static void lookup41()
{
	
	vector<string> temp;
	DIR *start;
	struct dirent *entry;
	char* x;	
	if((start=opendir(".")) == NULL) 
	{
		perror("opendir");
		if(-1 == closedir(start))
		{
			perror("closedir");
		}
		return;
	}
	
	do {
		errno = 0;
		if((entry = readdir(start)) != NULL) 
		{	
			if(entry->d_type == DT_DIR)
			{	
				x = entry->d_name;
				if(x[0] == '.' && x[1] == '.')
					continue;
				cout << x << ":" << endl;
				lookup_d1(x);
				
			}
			
		}	
		
	} while(entry != NULL);
	

	if(errno != 0)
	{
		perror("error reading directory");
		if(-1 == closedir(start))
		{
			perror("closedir");
		}
		return;
	}

	
	if(-1 == closedir(start))
	{
		perror("closedir");	
	}
	return;
}


//-R
static void lookup4()
{
	
	vector<string> temp;
	DIR *start;
	struct dirent *entry;
	char* x;

	if((start=opendir(".")) == NULL) 
	{
		perror("opendir");
		if(-1 == closedir(start))
		{
			perror("closedir");
		}
		return;
	}
	
	do {
		errno = 0;
		if((entry = readdir(start)) != NULL) 
		{	
			if(entry->d_type == DT_DIR)
			{						
				x = entry->d_name;
				if(x[0] == '.' && x[1] == '.')
					continue;
				cout << x << ":" << endl;
				lookup_d(x);
				
			}
		}	
		
	} while(entry != NULL);
	

	if(errno != 0)
	{
		perror("error reading directory");
		if(-1 == closedir(start))
		{
			perror("closedir");
		}
		return;
	}
	if(-1 == closedir(start))
	{
		perror("closedir");
	}
	return;
}

//-Rl
static void lookup42()
{
	
	vector<string> temp;
	DIR *start;
	struct dirent *entry;
	char* x;

	if((start=opendir(".")) == NULL) 
	{
		perror("opendir");
		if(-1 == closedir(start))
		{
			perror("closedir");
		}

		return;
	}
	
	do {
		errno = 0;
		if((entry = readdir(start)) != NULL) 
		{	
			if(entry->d_type == DT_DIR)
			{	
				x = entry->d_name;
				if(x[0] == '.' && x[1] == '.')
					continue;
				cout << x << ":" << endl;
				dlookup_d(x);
				
			}
			
		}	
		
	} while(entry != NULL);
	

	if(errno != 0)
	{
		perror("error reading directory");
		if(-1 == closedir(start))
		{
			perror("closedir");
		}
		return;
	}

	
	if(-1 == closedir(start))
	{
		perror("closedir");	
	}
	return;
}


int main( int argc, char *argv[]) {
	string flag = "-a";
	string flag2 = "-l";
	string flag3 = "-R";
	
	if(argc == 1)
	{	
		lookup();
		return 0;
	}
		
	int i = 1;
	for(; i < argc; ++i) {	
		if(argv[i][0] != '-'){
			lookup_d(argv[i]);
		}
		else if(argv[i] == flag) {
			if(argc >= 3) {
			if(argv[2] == flag2)
				lookup31();
			else if(argv[2] == flag3)
				lookup41();
			}
			else
				lookup2();
			
		}
		else if(argv[i] == flag2) {
			if(argc >= 3) {
			if(argv[2] == flag)
				lookup31();
			else if(argv[2] == flag3)
				lookup42();
			}
			else
				lookup3();
			
		}
		else if(argv[i] == flag3){
			if(argc >= 3) {
			if(argv[2] == flag)
				lookup41();
			else if(argv[2] == flag2)
				lookup42();
			}
			else
				lookup4();
		}				
		else if(strstr(argv[i], "a") != NULL)
		{
			if(strstr(argv[i], "l") != NULL)
				lookup31();
			if(strstr(argv[i], "R") != NULL)
				lookup41(); 	
		}
		else if(strstr(argv[i], "l") != NULL)
		{
			if(strstr(argv[i], "R") != NULL)
				lookup42();
		}	
	}
	
	
	return 0;
}
