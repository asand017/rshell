rshell
======

rshell assignment for cs100.

Summary:

rshell attempts to mimic a bash-like terminal shell. rshell accepts bash command executables
that exist in /bin, however it does not function with built-in bash commands, such as cd.

Functionality:

rshell features the following libraries:
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

rshell includes a special built in exit command, exit. Additionally it features a "$" command prompt at the beginning of 
each command line.

$ ls
$  a.out  rshell  rshell.cpp
$ pwd
/home/csmajs/asand017/rshell/src
$ echo test
test
$ mkdir cow
$ ls
$  a.out  cow  rshell  rshell.cpp
$ exit

Bugs:

rshell fails to accept flags, such as in executing ls -a, ls -l, or rm -rf, etc.

$ ls -a
ls: cannot access -: No such file or directory
ls: cannot access a: No such file or directory
$ rm -rf
rm: cannot remove `-': No such file or directory

Additionally, rshell fails completely at executing multiple commands on a single line.

$ ls&&pwd
ls: cannot access &: No such file or directory
ls: cannot access &: No such file or directory
ls: cannot access pwd: No such file or directory
$ ls -a; echo hello; mkdir test
ls: cannot access -: No such file or directory
ls: cannot access a: No such file or directory
ls: cannot access echo: No such file or directory
ls: cannot access hello: No such file or directory
ls: cannot access mkdir: No such file or directory
ls: cannot access test: No such file or directory
$ exit

rshell also has no implementation of the # character, so there is no functionality for comments.

Additional Files:

rshell comes with a Makefile and documentation of a MIT open source license.

