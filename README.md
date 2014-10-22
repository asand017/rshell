RSHELL
======

Licensing information: READ LICENSE
---
Project source can be downloaded at https://github.com/asand017/rshell.git
---------
Author and contribution list
---------------------
Aaron Sanders

All other known bugs can be sent to asand017@ucr.edu

File List
----------
'''
.:
Makefile
 
LICENSE

README.md

./src

./tests
...
...
./src:

rshell.cpp
'''
'''
./tests:

exec.script
'''
How to run file
-------------
In terminal:
1. $git clone http://github.com/yourusername/rshell.git
2. $cd rshell
3. $cd git checkout hw0
4. $make
5. $bin/rshell

Summary:

rshell attempts to mimic a bash-like terminal shell. rshell accepts bash command executables
that exist in /bin, however it does not function with built-in bash commands, such as cd.

Functionality:

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

Installation:
To install rshell, enter into the terminal command line, $make.

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

