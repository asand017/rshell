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
#include <signal.h>
#include <dirent.h>
#include <boost/algorithm/string.hpp>

using namespace std;

using namespace boost;

void sig_handler(int signum) {
	if(signum == SIGINT)
		return;	
		
	if(signum == SIGTSTP)
		return;
}

 void laydapipe(char **x, char **y) {
  
          int pfds[2];
          pid_t pid, pid2;
          int status, status2;
          pipe(pfds);
          if((pid = fork()) < 0) {
                  perror("fork");
                  exit(1);
          }
          if(pid != 0) {
                  if((pid2 = fork()) < 0) {
                          perror("fork");
                          exit(1);
                  }
          }
          if(pid == 0) {
                  close(1);
                  dup(pfds[1]);
                  close(pfds[0]);
                  close(pfds[1]);
                  if(execvp(x[0], x) < 0) {
                          perror("execvp");
                  }
		  //exit(0);
  //              close(pfds[1]);
          }
          else if(pid2 == 0) {
                  close(0);
                  dup(pfds[0]);
                  close(pfds[1]);
                  close(pfds[0]);
                  if(execvp(y[0], y) < 0) {
                          perror("execvp");
                  }
		  //exit(0);
  //              close(pfds[0]);
          }
          else {
	
                  close(pfds[0]);
                  close(pfds[1]);
                  if(-1 ==  wait(&status)) {
			perror("wait");
		  	cerr << "one" << endl;
		  }
		  //wait(&status) != pid;
                 // status2 = waitpid(pid2, &pid2, 0); 
		  if(-1 == wait(&status2)) { 
			perror("wait");
			cerr << "two" << endl;
		  }
		  //wait(&status2) != pid2;
 
          }
          return;
 }


void execvp(char **ye, int k) {
	char *kewl2 = getenv("PATH");
	if(kewl2 == NULL)
		perror("getenv");

	string kewl = kewl2;

	vector<string> vec;
	split(vec, kewl, is_any_of(":")); 
	
	errno = 0;
	string sweg;
	ye[k] = NULL;
        int pid = fork();
        if(pid == -1) {
       		perror("fork");
                exit(1);
        }
        if(pid == 0) {
       		
	//	int cpid = getpid();
		
	//	if(-1 == setpgid(pid, cpid))
	//		perror("setpgid");
	
	//	if(isatty(0))
	//		tcsetpgrp(0, pid);
		
	//	if(isatty(1))
	//		tcsetpgrp(1, pid);

	//	if(isatty(2))
	//		tcsetpgrp(2, pid);			
		
		signal(SIGTSTP, SIG_DFL);

		for(unsigned i = 0; i < vec.size(); ++i) {
			vec[i] += "/";
			vec[i] += ye[0];
	
			sweg = ye[0];
				
			if(sweg == "exit")
			{
				exit(1);
			}	
				
			int r = execv(vec[i].c_str(), ye);
               		if(r == -1) {
               		
				if((i + 1) == vec.size())
				{
					perror("execv");
					exit(1);
				}
				continue;
			}
	
         	} 
		if(sweg == "exit")
			exit(1);			
       		

	 }
      	else {
	//	struct terminos *blast;
//		setpgid(pid, pid);
	
		
	
		if(SIG_ERR == signal(SIGTSTP, SIG_IGN)){
			perror("signal");
		}
	
		if(sweg == "exit") {
			exit(1);	
		}
        	if(-1 == waitpid(pid, &pid, 0)) {
                          perror("waitpid");
                }
		if(WIFSIGNALED(pid)) {
			return;
		}
        }

}

void changedir(string caker) {	
	if(-1 == chdir(caker.c_str())){
		perror("chdir");
	}
	return;
}	

void rshell(string &x) {

	string bar = "|";
	size_t check = x.find(bar);
	if(check != string::npos) {
		if(x.at(check+1) != '|') {
			char *argv[9];
          		char *args[9];
       			vector<string> blast;
          		vector<string> laser;
          	//string x;
          	//getline(cin, x);
         	 	int i = 0;
         	 	int k = 0;
        		  typedef tokenizer< char_separator<char> > tokenizer;
       		  	 char_separator<char> sep (" ", "~<>>>\"#-;:\'||&&", drop_empty_tokens);
        	  	tokenizer tokens(x, sep);
     		   	  for(tokenizer::iterator tok_iter=tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
  
 		                 if(*tok_iter == "|") {
        	                  ++tok_iter;
        	        	          while(tok_iter != tokens.end()) {
  		
       		 	                          blast.push_back(*tok_iter);
       		         	                  args[i] = new char[12];
       	        	         	          strcpy(args[i], const_cast<char*>(blast[i].c_str()));
               	       		          	  ++i;
           	       		                ++tok_iter;
               	        	           continue;
                		          }
                	       	   break;
                	 	 }
  
 	           	      laser.push_back(*tok_iter);
 	           	      argv[k] = new char[12];
 	           	      strcpy(argv[k], const_cast<char*>(laser[k].c_str()));
 	           	      ++k;
 	        	 }
 	 		
		          argv[k] = NULL;
	       	 	  args[i] = NULL;
	       		  laydapipe(argv, args);
	 		return;
		}		
		
	}	
	
		
	char *argv[9];
	int i = 0;
	string going;
	string saad;
	vector<string> arg_s;	
	typedef tokenizer< char_separator<char> > tokenizer;
	char_separator<char> sep (" ", "~<>>>\"#-;:||&&", drop_empty_tokens);
	tokenizer tokens(x, sep);
	for(tokenizer::iterator tok_iter=tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {			 
		//cerr << going << endl;		
		if(saad == "-") {
			if(*tok_iter == "-") {
				saad += *tok_iter;
				going += *tok_iter;
				continue;
			}
			going += *tok_iter;
			going += " ";
		 	saad.append(*tok_iter);
			arg_s.push_back(saad);
			argv[i] = new char[12];
			strcpy(argv[i], const_cast<char*>(saad.c_str()));
			if(*tok_iter == "exit")
				exit(0);
                        ++i;
			delete [] argv[i]; //HEERRREEE
                        continue;               
                  
		  }

                  if(*tok_iter == "-") {
                        saad = *tok_iter;
			going += *tok_iter;
                        continue;       
                  }

	          if(*tok_iter == "#") {
			break;	
		  }

		  if(*tok_iter == ";") {
                        ++tok_iter;
		//	if(going == "")
		//		continue;
                        rshell(going);
                        going.erase(0, going.find(*tok_iter, i));
                        arg_s.clear();
                        i = 0;
//                        argv[i] = new char[12];
	          }
		
		  if(*tok_iter == "&") {
			++tok_iter;
			if(*tok_iter == "&") {
				++tok_iter;
		//		if(going == "")
		//			continue;
				rshell(going);
				going.erase(0, going.find(*tok_iter, i));
				arg_s.clear();
				i = 0;
//				argv[i] = new char[12];
			}
		  }

		  if(*tok_iter == "<") {
			++tok_iter;
			
			if(*tok_iter == "<") {
	
				++tok_iter;
		
				if(*tok_iter == "<") {
					++tok_iter;
					going += *tok_iter;
					string leggo;
				if(*tok_iter == "\"") {
				//	if(dup2(fd5, 0) == -1)
				//		perror("dup2");
					
				//	int savestdin = dup(0);
				//	if(savestdin == -1)
				//		perror("dup");
				//	if(*tok_iter == "\"") {	
						++tok_iter;
						while(*tok_iter != "\"") {
						//	int bag = write(fd5, buf, BUFSIZ); 
						//	if(bag == -1) {
						//		perror("write");
						//		exit(1);
						//	}	
	
							cout << *tok_iter << endl;
							leggo += *tok_iter;
							leggo += " ";
							++tok_iter;
						}
						leggo += *tok_iter;
						going += " ";
						going += leggo;
						cout << leggo << endl;
						//int bag = write(fd2, buf, BUFSIZ);
						//if(bag == -1) {
						//	perror("write");
						//	exit(1);
						//}
					}
				//	int claw = read(fd2, buf, BUFSIZ);
				//	if(claw == -1)
				//		perror("read");
					
			//		int mk = close(fd5);
			//		if(mk == -1)
			//			perror("close");
			//		delete [] buf;
			//		if(dup2(savestdin, 0) == -1)
			//			perror("dup2");
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
	

		  if(*tok_iter == "0") {
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
					int grag = dup2(fd2, 0);
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
					int drag = dup2(fd, 0);
					if(drag == -1) {
						perror("dup2");
						exit(1);
					}
					continue;
				}
		  	}

	
		  }

		  if(*tok_iter == "1") {
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
		  }	
		
		  if(*tok_iter == "2") {
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
					int grag = dup2(fd2, 2);
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
					int drag = dup2(fd, 2);
					if(drag == -1) {
						perror("dup2");
						exit(1);
					}
					continue;
				}
		  	}	
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
			//tokenizer::iterator coward;
			if(*tok_iter != "|") {
			//piping
			/*	
				char *ant[9];
				char *spider[9];
          			vector<string> blast;
         			vector<string> laser;
          			int a = 0;
          			int b = 0;	
          			char_separator<char> sep2 (" ", "~<>>>\"#-;:\'||&&", drop_empty_tokens);
          			tokenizer tokens2(x, sep2); //here is the issue
          			for(tokenizer::iterator tok_iter2=tok_iter; tok_iter2 != tokens2.end(); ++tok_iter2) {
  				//	cerr << *tok_iter2 << endl;
 			                if(*tok_iter2 == "|") {
                        	//	cerr << *tok_iter << endl; 
				//	blast.push_back(*tok_iter2);
				//	cerr << blast[a] << endl;
				//	spider[a] = new char[12];
				//	strcpy(spider[a], const_cast<char*>(blast[a].c_str()));
				//	++a;
						++tok_iter2;
						++tok_iter;
                          	 		while(tok_iter2 != tokens2.end() ) {
  
                                 			blast.push_back(*tok_iter2);
                                  			cerr << blast[a] << endl;
							spider[a] = new char[12];
                                  			strcpy(spider[a], const_cast<char*>(blast[a].c_str()));
                                  			++a;
                                  			++tok_iter2;
							++tok_iter;
                                  	
						}	cerr << "got to this point" << endl;	
	                        	
						break;
					}
					//cerr << *tok_iter2 << endl;
                         		//break;
                 			//tok_iter = tok_iter2;
 					//break; 
                 			laser.push_back(*tok_iter2);
                  			ant[b] = new char[12];
                  			strcpy(ant[b], const_cast<char*>(laser[b].c_str()));
                  			++b;
          			}
 				cerr << "sweg" << endl;
          			ant[b] = NULL;
          			spider[a] = NULL;
         			laydapipe(ant, spider);
				cerr << "here" << endl;	
				return;
				//delete **spider;
				*/	
			}
			else if(*tok_iter == "|") {
				++tok_iter;
		//		if(going == "")
		//			continue;
				rshell(going);
				going.erase(0, going.find(*tok_iter, i));
				arg_s.clear();
				i = 0;
			//	argv[i] = new char[12];
			}	
		
		  }

		 if(*tok_iter == "cd")
		 {
			
			++tok_iter;	
			string joker = *tok_iter;

			if(joker == ".") {
				++tok_iter;
				if(*tok_iter == ".")
					joker += *tok_iter;
			}
	
			if(joker.at(joker.size()-1) != '/'){
			
				joker += "/";
			}

			changedir(joker);
			continue;
		  }
		
		  tokenizer::iterator daw = tok_iter;                  
		  string lop = *tok_iter;
		  string llop;
		  if((*tok_iter).size() == 1) {
			string lodge = *tok_iter;
			++tok_iter;
			if(tok_iter == tokens.end()) {
				arg_s.push_back(lodge);
				argv[i] = new char[12];
				strcpy(argv[i], const_cast<char*>(arg_s[i].c_str()));
			
				++i;
				break;;
			}
			else if(*tok_iter == "-") {
				llop += lop;
				llop += *tok_iter;
		//		cerr << mok << endl;
				++tok_iter;
		//		llop += *tok_iter;
		//		cerr << mok << endl;
		//		++tok_iter;
				llop += *tok_iter;
				llop += " ";
		//		cerr << mok << endl;
				++tok_iter;
			
				going += llop;
				going += " ";
		

				arg_s.push_back(llop);
				argv[i] = new char[12];
				strcpy(argv[i], const_cast<char*>(arg_s[i].c_str()));
				++i;
				continue;		
			}
			tok_iter = daw;
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
	int v = 0;
	while(v <= i) {
		delete [] argv[v];
		++v;
	}
	//delete [] *argv;
	return;	
}

int main()
{
	int oldstdin = dup(0);

	if(oldstdin == -1) 
		perror("dup");


	int oldstdout = dup(1);

	if(oldstdout == -1) 
		perror("dup");	


	int oldstderr = dup(2);

	if(oldstderr == -1) 
		perror("dup");	
	
	//getting login and hostname
	char *x = getlogin();
	if(x == NULL) {
		perror("getlogin");
	}
	char blak [256];	
	size_t len = 64;
	if(-1 == gethostname(blak, len)) {
		perror("gethostname");	
	}

	if(SIG_ERR == signal(SIGINT, sig_handler))
	{
		perror("signal");	
	}	
	if(SIG_ERR == signal(SIGTSTP, sig_handler))
	{
		perror("signal");	
	}	
	//the rshell
	string args;
	while(1 != 2)
	{
		char buffer [256];
		size_t size = 100;
		char* cwd = getcwd(buffer, size);
		if(cwd == NULL)
			perror("getcwd");
		
		cout << x << "@" << blak << buffer << "$ ";

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
