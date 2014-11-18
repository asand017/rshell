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
#include <sys/stat.h>
#include <fcntl.h>

int oldstdin = dup(0);
int oldstdout = dup(1);
int oldstderr = dup(2);

using namespace std;
using namespace boost;

void execvp(char **ye, int k) {
	ye[k] = NULL;
        int pid = fork();
        if(pid == -1) {
       		perror("fork");
                exit(1);
        }
        if(pid == 0) {
        	int r = execvp(ye[0], ye);
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
	

void rshell(string &x) {
	char *argv[9];
	int i = 0;
	string going;
	string saad;
	vector<string> arg_s;	
	typedef tokenizer< char_separator<char> > tokenizer;
	char_separator<char> sep (" ", "<>>>\"#-;||&&", drop_empty_tokens);
	tokenizer tokens(x, sep);
	for(tokenizer::iterator tok_iter=tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
		 if(saad == "-") {
			going += *tok_iter;
			going += " ";
		 	saad.append(*tok_iter);
			arg_s.push_back(saad);
			argv[i] = new char[12];
			strcpy(argv[i], const_cast<char*>(saad.c_str()));
			if(*tok_iter == "exit")
				exit(0);
                        ++i;
                        continue;               
                  
		  }

                  if(*tok_iter == "-") {
                        saad = *tok_iter;
			going += *tok_iter;
			going += " ";
                        continue;       
                  }

	          if(*tok_iter == "#") {
			break;	
		  }

		  if(*tok_iter == ";") {
                        ++tok_iter;
                        rshell(going);
                        going.erase(0, going.find(*tok_iter, i));
                        arg_s.clear();
                        i = 0;
                        argv[i] = new char[12];
	          }
		
		  if(*tok_iter == "&") {
			++tok_iter;
			if(*tok_iter == "&") {
				++tok_iter;
				rshell(going);
				going.erase(0, going.find(*tok_iter, i));
				arg_s.clear();
				i = 0;
				argv[i] = new char[12];
			}
		  }

		  if(*tok_iter == "<") {
			++tok_iter;
	
			if(*tok_iter == "<") {
				++tok_iter;
				if(*tok_iter == "<") {
					//extra credit one
				}
			}
			string cake = *tok_iter;
			int fd = open(cake.c_str(), O_RDWR);
			if(fd == -1) {
				perror("open");
				exit(1);
			}
			int drag = dup2(fd, 0);
			if(drag == -1) {
				perror("dup2");
				exit(1);
			}
			continue;
		  }
	

		  if(*tok_iter == ">") {
			++tok_iter;
			if(*tok_iter == ">") {
				++tok_iter;
				string got = *tok_iter;
				int fd2 = open(got.c_str(), O_RDWR|O_CREAT);
				if(fd2 == -1) {
					perror("open");
					exit(1);
				}
				//COME FIX STDERROR LATER
				int dragon = dup2(fd2, 2);
				if(dragon == -1) {
					perror("dup2");
					exit(1);
				}
				continue;	
			}
			else {	
				string hold = *tok_iter;
				int fd = open(hold.c_str(), O_RDWR|O_CREAT);
				if(fd == -1) {
					perror("open");
					exit(1);
				}

				int drag = dup2(fd, 1);
				if(drag == -1) {
					perror("dup2");
					exit(1);
				}
				continue;
			}
		  }

		  if(*tok_iter == "|") {
			++tok_iter;
			
			//piping
			int pipefd[2];
			pid_t cpid;
			char buf;
			

			if(*tok_iter == "|") {
				++tok_iter;
				rshell(going);
				going.erase(0, going.find(*tok_iter, i));
				arg_s.clear();
				i = 0;
				argv[i] = new char[12];
			}	
		
		  }

		  going += *tok_iter;
		  going += " ";

		  arg_s.push_back(*tok_iter);
		  argv[i] = new char[12];
	 	  strcpy(argv[i], const_cast<char*>(arg_s[i].c_str()));
		  
		  if(*tok_iter == "exit")
			exit(0);
		
		  ++i;
			
	}
	
	execvp(argv, i);

	return;	
}

int main()
{
	string args;
	while(1 != 2)
	{
		cout << "$ ";
		getline(cin, args); 	
		rshell(args);
		
		int ok = dup2(oldstdin, 0);
		if(ok == -1) {
			perror("dup2");
			exit(1);
		}
		int ok2 = dup2(oldstdout, 1);
		if(ok2 == -1) {
			perror("dup2");
			exit(1);
		}
		int ok3 = dup2(oldstderr, 2);
		if(ok3 == -1) {
			perror("dup2");
			exit(1);
		}			
	}                        
	
	return 0;
}
