#include <boost/tokenizer.hpp>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <cstdlib>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
using namespace boost;

int main()
{
	int yas_and = 0;
	int yas_or = 0;
	string args;
	while(1 != 2)
	{
		cout << "$ ";
		getline(cin, args); 	
		
		string saad;
		char *argv[9];
		int i = 0;
		vector<string> arg_s;
		typedef tokenizer< char_separator<char> > tokenizer;
		char_separator<char> sep(" ", "-;||&&", drop_empty_tokens);
		tokenizer tokens(args, sep);
		for(tokenizer::iterator tok_iter=tokens.begin(); tok_iter != tokens.end();++tok_iter) {
			if(yas_and == 1){
				if(*tok_iter == "&") {
					++tok_iter;
					//arg_s.push_back(*tok_iter);
					//argv[i] = new char[12];
					//strcpy(argv[i], const_cast<char*>(arg_s[i].c_str()));
					//if(*tok_iter == "exit")
					//	exit(1);
					//++i;

					argv[i] = NULL;
					int pid2 = fork();
					if(pid2 == -1) {
						perror("fork");	
						exit(1);
					}
					if(pid2 == 0) {
						int r = execvp(argv[0], argv);
						if(r == -1) {
							perror("execvp");
							exit(1);
						}
					}
					else {
						if(-1 == waitpid(pid2, &pid2, 0)) {
							perror("waitpid");
						}
					}
				}
			}
			if(yas_or == 1){
				if(*tok_iter == "|") {
					++tok_iter;
					//arg_s.push_back(*tok_iter);
					//argv[i] = new char[12];
					//strcpy(argv[i], const_cast<char*>(arg_s[i].c_str()));
					//if(*tok_iter == "exit")
					//	exit(1);
					//++i;


					argv[i] = NULL;
					int pid2 = fork();
					if(pid2 == -1) {
						perror("fork");	
						exit(1);
					}
					if(pid2 == 0) {
						int r = execvp(argv[0], argv);
						if(r == -1) {
							perror("execvp");
							exit(1);
						}
					}
					else {
						if(-1 == waitpid(pid2, &pid2, 0)) {
							perror("waitpid");
						}
					}
				}
			}

			if(saad == "-") {
				saad.append(*tok_iter);
				arg_s.push_back(saad);
				argv[i] = new char[12];
				strcpy(argv[i], const_cast<char*>(saad.c_str()));
				if(*tok_iter == "exit")
					exit(1);
				++i;
				continue;		
			}
			if(*tok_iter == "-") {
				saad = *tok_iter;
				continue;	
			}
			
			if(*tok_iter == "&") {
				++yas_and;
				continue;
			}
			else if(*tok_iter == "|") {
				++yas_or;
				continue;
			}
			else if(*tok_iter == ";") {
				++tok_iter;
				argv[i] = NULL;	
				int pid2 = fork();
				if(pid2 == -1) {
					perror("fork");	
					exit(1);
				}
				if(pid2 == 0) {
					string temp = *tok_iter;
					int r = execvp(const_cast<char*>(temp.c_str()), argv);
					if(r == -1) {
						perror("execvp");
						exit(1);
					}
				}
				else {
					if(-1 == waitpid(pid2, &pid2, 0)) {
						perror("waitpid");
					}
				}

			}
			else {

				arg_s.push_back(*tok_iter);
				argv[i] = new char[12];
				strcpy(argv[i], const_cast<char*>(arg_s[i].c_str()));
				if(*tok_iter == "exit")
					exit(1);
				++i;
			}
		}
		argv[i] = NULL;	
		int pid = fork();
		if(pid == -1) {
			perror("fork");
			exit(1);
		}
		if(pid == 0) {
			int r = execvp(argv[0], argv);
			if(r == -1) {
				perror("execvp");
				exit(1);
			}
		}
		else {
			if(-1 == waitpid(pid, &pid, 0)) {
				perror("waitpid");
			}
		}
	
	}

	return 0;
}
