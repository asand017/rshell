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

//using namespace boost;
using namespace std;

int main()
{
	using namespace boost;
	string args;
	while(1 != 2)
	{
		cout << "$ ";
		getline(cin, args); 	
		
		char *argv[9];
		int i = 0;
		vector<string> arg_s;
		typedef tokenizer< char_separator<char> > tokenizer;
		char_separator<char> sep(" ", "-;||&&", drop_empty_tokens);
		tokenizer tokens(args, sep);

		for(tokenizer::iterator tok_iter=tokens.begin(); tok_iter != tokens.end();++tok_iter) {
			if(*tok_iter == "&&" || *tok_iter == "||" || *tok_iter == ";") {
		
	//			argv[i] = NULL;
	//			int pidb = fork();
	//			if(pidb == -1) {
	//				perror("fork");
	//			}
	//			if(pidb == 0) {
	//				int t = execvp(argv[0], argv);
	//				if(t == -1) {
	//					perror("execvp");
	//				}
	//			}
	//			else {
	//				if(-1 == waitpid(pidb, &pidb, 0)) {
	//					perror("waitpid");
	//				}
	//			}
			}
			else {
				cout << *tok_iter << endl;
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

//	int pid = fork();
//	if(pid == -1) {
//		perror("fork");
//		exit(1);
//	}
//	if(pid == 0)
//	{
		//char *argv2[4];
		//argv2[0] = new char[6];
		//strcpy(argv[0], "ls");
		//argv2[1] = new char[6];
		//strcpy(argv[1], "-a");
		//argv2[2] = new char [6];
		//strcpy(argv[2], "-l");
	
	//	int pid2 = fork();
	//	if(pid2 == -1) {
	//		perror("fork");
	//		exit(1);
	//	}	
	//	if(pid2 == 0) {
	///		if(execvp(argv[0], argv) == -1) {
	//			perror("execvp");	
	//			exit(1);
	//		}
	//	}
	//	else {
	//		if(-1 == waitpid(pid2,&pid2,0 ))
	//			perror("waitpid");
	//	}
	//	
	  //      if(execvp(argv[1], argv) == -1) {
	//		perror("execvp");
	//		exit(1);
	//	}
//
//		cout << "after" << endl;
//	}
//	else {
//		if(-1 == waitpid(pid, &pid, 0))
//			perror("waitpid");
//	}
	
	}

	return 0;
}
