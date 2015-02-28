myshell: myshell.c myshell.h utility.c inner.c out.c
	gcc -O2 -Wall -g myshell.c utility.c inner.c out.c -o myshell
