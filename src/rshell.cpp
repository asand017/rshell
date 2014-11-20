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
	for(tokenizer::iterator tok_iter=tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {			 if(saad == "-") {
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
			//	going += *tok_iter;
				++tok_iter;
			//	going += *tok_iter;
				if(*tok_iter == "<") {
					//EXTRA CREDIT 1 HERE!!!!!!!!!!!
					string blah = "ok";
					void *buf;
					int fd2 = creat(const_cast<char*>(blah.c_str()), S_IRWXU);
					if(fd2 == -1) {
						perror("creat");
						exit(1);
					} 
					++tok_iter;
					going += *tok_iter;
					string leggo;
					if(*tok_iter == "\"") {
						++tok_iter;
						while(*tok_iter != "\"") {
							cout << *tok_iter << endl;
							leggo += *tok_iter;
							leggo += " ";
							++tok_iter;
						}
						buf = malloc(leggo.length());
						//leggo += *tok_iter;
						//going += " ";
						//going += leggo;
						int bag = write(fd2, buf, leggo.length());
						if(bag == -1) {
							perror("write");
							exit(1);
						}
					}
				}
			}
			string cake = *tok_iter;
			int savestdin;
			if(-1 == (savestdin = dup(0))) {
				perror("dup");
				exit(1);
			}
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
			//if(-1 == dup2(savestdin, 0))
			//{
			//	perror("dup2");
			//	exit(1);
			//}
			continue;
		  }
	

		  if(*tok_iter == ">") {
			++tok_iter;
			if(*tok_iter == ">") {
				++tok_iter;
				string swerve = *tok_iter;
				int fd2 = open(swerve.c_str(), O_RDWR|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
				if(fd2 == -1) {
					perror("open");
					exit(1);
				}
				int grag = dup2(fd2, 1);
				if(grag == -1) {
					perror("dup2");
					exit(1);
				}
				continue;
			}
			else {	
				string hold = *tok_iter;
				int fd = open(hold.c_str(), O_RDWR|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR);
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
			tokenizer::iterator coward;
			if(*tok_iter != "|") {
			//piping
			int pipefd[2];
			pid_t cpid;
			//char buf;
			if(pipe(pipefd) == -1) {
				perror("pipe");
				exit(1);
			}
			cpid = fork();
			if(cpid == -1) {
				perror("fork");
				exit(1);
			}
			else if(cpid == 0) {
				if(-1 == dup2(pipefd[1],1))
				{
					perror("dup2");
					exit(1);
				}
				if(-1 == close(pipefd[0]))
				{
					perror("close");
					exit(1);
				}
				argv[i] = NULL;
				if(-1 == execvp(argv[0], argv))
				{
					perror("execvp");
				}
				exit(1);
			}
			else if(cpid > 0)
			{
				int savestdin;
				if(-1 == (savestdin = dup(0)))
				{
					perror("dup");
					exit(1);
				}
				if(-1 == dup2(pipefd[0], 0)) {
					perror("dup2");
					exit(1);
				}
				if(-1 == close(pipefd[1])) {
					perror("close");
					exit(1);
				}
				if(-1 == waitpid(cpid, &cpid, 0)) {
					perror("waitpid");
					exit(1);
				}
				int pipefd2[2];
				pid_t cpid2;
				if(pipe(pipefd2) == -1) {
					perror("pipe");
					exit(1);
				}
				cpid2 = fork();
				if(cpid2 == -1) {
					perror("fork");
					exit(1);
				}
				else if(cpid2 == 0) {
					if(-1 == dup2(pipefd2[0], 0))
					{
						perror("dup2");
						exit(1);
					}
					if(-1 == close(pipefd2[1])) 
					{
						perror("close");
						exit(1);
					}
					coward = tok_iter;
					char *toby[9];
					int l = 0;
					vector<string> baby;
					string mok;
					while(tok_iter != tokens.end()) {
						if(*tok_iter == "|")
							rshell(going);

						mok += *tok_iter;
						mok += " ";
						baby.push_back(*tok_iter);
						toby[l] = new char [12];
						strcpy(toby[l], const_cast<char*>(baby[l].c_str()));
						going += mok;
						++l;
					}
					toby[l] = NULL;
					if(-1 == execvp(toby[0], toby))	
						perror("execvp");
					
					exit(1);
				}
				else if(cpid > 0) {
					int savestdout;
					if(-1 == (savestdout = dup(1)))
					{
						perror("dup");
						exit(1);
					}
					if(-1 == dup2(pipefd2[1], 1)) {
						perror("dup2");
						exit(1);
					}
					if(-1 == close(pipefd2[0])) {
						perror("close");
						exit(1);
					}
					if(-1 == waitpid(cpid2, &cpid2, 0)) {
						perror("waitpid");
						exit(1);
					}
					if(-1 == dup2(savestdout, 1))
						perror("dup2");
				}
					if(-1 == dup2(savestdin, 0))
						perror("dup2");
				}
				/*
				coward = tok_iter;
				char *toby[9];	
				int l = 0;
				vector<string> baby;
				string mok;
				int kpid = fork();
				if(kpid == -1) {
					perror("fork");
					exit(1);
				}
				else if(kpid == 0) {
					if(-1 == dup2(pipefd[0], 0)) {
						perror("dup2");
						exit(1);
					}
					//if(-1 == close(pipefd[1]))
					//{
					//	perror("close");
					//	exit(1);	
					//}
					while(tok_iter != tokens.end()) {
						if(*tok_iter == "|")
							rshell(going);
	
						mok += *tok_iter;
						mok += " ";	
						baby.push_back(*tok_iter);
						toby[l] = new char[12];
						strcpy(toby[i], const_cast<char*>(baby[l].c_str()));
						going += mok;
						//APPEND TOBY TO ARGV SOMEHOW
						++l;		
					}
					toby[l] = NULL;
					if(-1 == execvp(toby[0], toby)) {
						perror("execvp");
					}
					exit(1);
				}
				else if(kpid > 0) {
					if(-1 == waitpid(kpid, &kpid, 0)) {
						perror("waitpid");
						exit(1);
					}
				}				
				
				tok_iter = coward;
				
				if(-1 == dup2(savestdin, 0)) {
					perror("dup2");
					exit(1);
				}
				}
				continue;
				*/
			}
			//end piping	

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
