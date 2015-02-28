/*
 * Filename:myshell.h
 * Description: The head file of myshell.c utitlity.c inner.c out.c
 *		There are declarationis of funtions and global variables
 * Author: Xu Yuhao
 * Created: 2014.7.30
 */
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <pwd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MAXCHILD 1000
#define MAX_LINE 80 /* The maximum length command */
struct passwd *pwd;
void init_env();/*init the environment*/
int get_args(); /*read user input and return the number of args*/
void out_parse(); /*when pro the outter Cmd,test if there is > >> < & */
void print_CMD();/*print the command prompt*/
void add_env_PATH(char * ); /*add <pathname>/myshell to PATH*/
int if_inner_cmd();/*test if it is a inner cmd*/
int inner_pro();/*do the inner cmd,return should_run*/
void out_pro();/*do the out cmd*/
void change_direct(); /*change the dierct target of IO*/
void do_cd();/*the inner cmd cd*/
void do_dir(char *,int); /*the inner cmd dir*/
void do_echo(); /*the inner cmd echo*/
void clean(); /*free and process the rubbish */

#ifndef GLOBAL
#define GLOBAL
char* IN_FILE;  /*the redirect stdin file*/
char* OUT_FILE; /*the redirect stdout file*/
int BACKGROUND; /*whether myshell should run in background.*/
int OUT_REDIRECT;/*whether myshell should stdout to other place*/
int OUT_REDIRECT_APPEND;/*whether myshell should stdout to other place appendly*/
int IN_REDIRECT;/*whether myshell should stdin from other place*/
pid_t CHILDTABLE[MAXCHILD]; /*store the child processes*/
char *ARGS[MAX_LINE/2 + 1]; /* command line arguments */
int NUMBER_ARGS; /* the number of args */
char *PATH; /*the enviromental PATH*/
#endif


