/*
 * Filename: inner.c
 * Description: Processing about inner CMD of myshell.
 * Author: Xu Yuhao
 * Created: 2014.7.30
 */

#include "myshell.h"
	
int inner_pro()
{
	int fd2,fd_out;
	/*pro with out_redirect > >> */
	if(NUMBER_ARGS > 2)
	{
 		
		if(strcmp(ARGS[NUMBER_ARGS-2],">")==0)
                {
                        OUT_REDIRECT = 1;
                        OUT_FILE = ARGS[NUMBER_ARGS-1];
			fd_out = open(OUT_FILE, O_WRONLY|O_CREAT|O_TRUNC, 0666);
              		fd2=dup(STDOUT_FILENO);   
              		dup2(fd_out, STDOUT_FILENO);  //redirect stdout to out file
              		close(fd_out);
			free(ARGS[NUMBER_ARGS-1]);
			free(ARGS[NUMBER_ARGS-2]);
                        NUMBER_ARGS -= 2;
                }
                else if(strcmp(ARGS[NUMBER_ARGS-2],">>")==0)
                {
                        OUT_REDIRECT_APPEND = 1;
                        OUT_FILE = ARGS[NUMBER_ARGS-1];
                        fd_out = open(OUT_FILE, O_WRONLY|O_APPEND, 0666);
                        fd2=dup(STDOUT_FILENO);       
                        dup2(fd_out, STDOUT_FILENO);  //redirect stdout to out file
                        close(fd_out);
			free(ARGS[NUMBER_ARGS-1]);
                        free(ARGS[NUMBER_ARGS-2]);
                        NUMBER_ARGS -= 2;

                }
	}
	/*end of out_redirect*/

	/*pro these inner CMD*/
	if(strcmp(ARGS[0],"cd") == 0)
	{
		do_cd();
	}
	else if(strcmp(ARGS[0],"clr") == 0)
	{
		system("clear");
	}
	else if(strcmp(ARGS[0],"dir") == 0)
	{
                char *dir_path = NULL;
		pwd = getpwuid(getuid());
                char *path = (char *)malloc(sizeof(char)*50);
		getcwd(path,50);
		//If the path has "~",replace "~" by the real path.
                if(ARGS[1][0] == '~')
                {
                    dir_path = malloc(strlen(pwd->pw_dir)+strlen(ARGS[1]));
                    //'~' makes length 1 more,but instead of '\0'
                    if(dir_path == NULL)  printf("dir:malloc failed.\n");
                    strcpy(dir_path,pwd->pw_dir);
                    strncpy(dir_path+strlen(pwd->pw_dir),ARGS[1]+1,strlen(ARGS[1]));
                }
                else //The path without "~"
                {
                        dir_path = malloc(strlen(ARGS[1]+1));
                	if(dir_path == NULL)	 printf("dir:malloc failed.\n");
                	strcpy(dir_path,ARGS[1]);
                }
		do_dir(dir_path,0);/*recuison list files in directory*/
                chdir(path);
		free(dir_path);
		free(path);
	} 
	else if(strcmp(ARGS[0],"environ") == 0)
	{
		system("echo $PATH");	
	}	
	else if(strcmp(ARGS[0],"echo") == 0)
	{
		do_echo(NUMBER_ARGS);
	}
	else if(strcmp(ARGS[0],"help") == 0)
	{
		system("more readme.txt");	
	}
	else if(strcmp(ARGS[0],"quit") == 0)
	{
		return 0; // should_run will be 0 and the program will quit
	}
	/*end of inner_CMD*/
	/*return the redirect output to the standard stdout*/
	if(OUT_REDIRECT || OUT_REDIRECT_APPEND)
	{
		dup2(fd2, STDOUT_FILENO);   
		close(fd2);  	
	}
	return 1;
}

void do_cd()
{	
	char *cd_path = NULL;
	pwd = getpwuid(getuid());
	if(NUMBER_ARGS == 1)
	/*if the CMD is cd*/
	{
		cd_path = malloc(strlen(pwd->pw_dir)+1);
		strcpy(cd_path,pwd->pw_dir);
	}
        else
	{
		/*If the path has "~",replace "~" by the real path.*/
		if(ARGS[1][0] == '~')
       	 	{
            		cd_path = malloc(strlen(pwd->pw_dir)+strlen(ARGS[1]));
            		//'~' makes length 1 more,but instead of '\0'
            		if(cd_path == NULL)	printf("cd:malloc failed.\n");
            		strcpy(cd_path,pwd->pw_dir);
            		strncpy(cd_path+strlen(pwd->pw_dir),ARGS[1]+1,strlen(ARGS[1]));
       		}
        	else //The path without "~"
        	{
            		cd_path = malloc(strlen(ARGS[1]+1));
            		if(cd_path == NULL)	printf("cd:malloc failed.\n");
            		strcpy(cd_path,ARGS[1]);
        	}
	}
        if(chdir(cd_path)!= 0)
            printf("myshell: cd: %s:%s\n",cd_path,strerror(errno));
        free(cd_path);
}

void do_dir(char* dir,int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	//test whether the directry exsits
	if((dp=opendir(dir)) == NULL)
	{
		fprintf(stderr,"cannot open directory:%s\n",dir);
		return;
	}
	chdir(dir); //enter the directory
	while((entry = readdir(dp)) != NULL)
	{
		lstat(entry->d_name,&statbuf); //get the stat struct
		if(S_ISDIR(statbuf.st_mode))
		{
			/*test if this struct is a directory too*/
			if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0 )
				continue; /*test if it is "." or ".."*/
			printf("%*s%s\n",depth," ",entry->d_name);
			/*recursion of child directory*/
			do_dir(entry->d_name,depth+4);
		}
		else printf("%*s%s\n",depth," ",entry->d_name);
	}
	chdir("..");
	closedir(dp);
}

void do_echo()
{
	int i;
	for(i = 1; i < NUMBER_ARGS; i ++)
	{
		if(ARGS[i] == NULL)
			break;
		printf("%s ",ARGS[i]);
	}
	printf("\n");
}




