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

How to run file
-------------
In terminal:
1. $git clone http://github.com/yourusername/rshell.git
2. $cd rshell
3. $make
4. $bin/rshell
4. $bin/ls
4. $bin/cp [option 1] [option 2]

Summary:

rshell attempts to mimic a bash-like terminal shell. rshell accepts bash command executables
that exist in /bin, including cd (excluding *cd* or *cd~* )
rshell can also execute output (>, >>)  and input (<) redirection.

ls mimics the GNU ls command and is functional for the "-a", "-l", and "-R" flags.

cp mimics the cp bash command.

Functionality:

rshell does virtually everything the bash shell does, save for some subtleties.  

asand017@cs100:~/rshell/src (master) $ rshell

$ ls -l; echo test && pwd || ls
total 88

-rwx------ 1 asand017 csmajs 17716 Nov 11 23:30 a.out
-rw------- 1 asand017 csmajs  4803 Nov 11 23:56 cp.cpp
-rw------- 1 asand017 csmajs  9101 Nov 11 23:56 ls.cpp
-rwx------ 1 asand017 csmajs 39721 Nov 16 19:34 rshell
-rwx------ 1 asand017 csmajs  2852 Nov 16 19:34 rshell.cpp
-rw------- 1 asand017 csmajs  2701 Nov 11 23:56 Timer.h
test
/home/csmajs/asand017/rshell/src
a.out  cp.cpp  ls.cpp  rshell  rshell.cpp  Timer.h
$ ls # -lR /
a.out  cp.cpp  ls.cpp  rshell  rshell.cpp  Timer.h



rshell input and output redirection.
$ echo test > testing
$ cat testing
test
$ echo A > echo B > echo C > echo D > testing
$ cat testing
A B C D
$ cat < testing
A B C D
$ echo swagger >> testing
$ cat testing
A B C D
swagger
$ cat < ls > testing


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

ls can handle flags -a:
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ g++ ls.cpp
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ a.out
a.out             cp.cpp            ls.cpp            rshell.cpp        Timer.h      

-l:
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ a.out -l
total 66893
-rwx------ 1 36790 950 46923 1415776375sec a.out
-rw------- 1 36790 950 4803  1415682389sec cp.cpp
-rw------- 1 36790 950 9184  1415775286sec ls.cpp
-rwx------ 1 36790 950 3282  1415323849sec rshell.cpp
-rw------- 1 36790 950 2701  1415749649sec Timer.h
error reading directory: Permission denied

and -R:
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ a.out -R
.:
a.out             cp.cpp            ls.cpp            rshell.cpp        Timer.h           

ls can also output the files of a user defined directory:
bin               boot              C:\nppdf32Log\debuglog.txt  cgroup            class             
dev               etc               extra             home              lib               lib64             lost+found        media             misc              mnt               net               opt               proc              root              sbin              selinux           srv               sys               tmp               usr               var               



cp works exactly as expected from the original function: 

%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ g++ cp.cpp
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ ls
a.out  cp.cpp  ls.cpp  rshell.cpp  Timer.h
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ touch test
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ vim test
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ cat test
dfwqefweqfeqwfewfewfw
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ a.out test test2
%%%%%%%%%%asand017@cs100:~/rshell/src (ls) $ cat test2
dfwqefweqfeqwfewfewfw


Installation:
To install rshell, enter into the terminal command line, "$make".

Bugs:

ls output has somewhat abnoraml spacing, although it is mainly an aesthetic bug. ls -l prints an error message at the end of completion. While the data is correct, this is a bug that was too hidden for me to find in time. Additionally, ls -l can only output the numerical user and group ids. Also, the last modified date is in raw seconds. Combinations of the ls flags will only work with up to two combined flags. 

rshell is unable to complete piped commands. It has difficulty parsing the right side of the pipe and as a result cannont complete the piping process.


