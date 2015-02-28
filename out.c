/*
 * Filename:out.c
 * Description: Processing about out CMD of myshell.
 * Author: Xu Yuhao
 * Created: 2014.7.30
 */

#include "myshell.h"

void out_pro()	
{
	/*if myshell*/
	if(strcmp(ARGS[0], "myshell") == 0)
	{
 		strcpy(ARGS[0], "bash");
 		if(ARGS[1] == NULL)
		{
    	              printf("myshell the file is NULL\n");
 	              return;
              	}
        }
	/*end of myshell*/

	pid_t pid = fork();
	if(pid < 0)
	{
		printf("Myshell error: fork failed!\n");
		return;
	}
	else if(pid == 0 )
	{//child
		change_direct();
          	execvp(ARGS[0],ARGS);
	}
	else if(pid > 0)
	{//father
		if(BACKGROUND)
		{
			printf("%u\n",pid);
			/*Do not run too many background processes*/
			int i;
			for(i = 0;i < MAXCHILD;i++)
			{
				if(CHILDTABLE[i] == 0)
				{
					CHILDTABLE[i] = pid; //store a child process
					break;
				}
			}
			if(i == MAXCHILD)
				perror("Too many background processes\n");
		}
		else
		{
			waitpid(pid,NULL,0); // wait for child process
		}
	}

}

void out_parse()
{
	int i;
	/*Background cmd*/
	if(strcmp(ARGS[NUMBER_ARGS-1],"&") == 0)
	{
		BACKGROUND = 1;
		free(ARGS[NUMBER_ARGS-1]);
		ARGS[NUMBER_ARGS-1] = NULL;
		NUMBER_ARGS --;
	}
	/*end of background cmd*/	
	/*Redirect cmd*/
	for(i = 0; i < NUMBER_ARGS;)
	{
		if(strcmp(ARGS[i],"<<")==0 || strcmp(ARGS[i],"<")==0)
        	{
            		IN_REDIRECT = 1;
            		IN_FILE = ARGS[i+1];
			free(ARGS[i]);
			ARGS[i] = NULL;
			i+=2;
        	}
        	else if(strcmp(ARGS[i],">")==0)
        	{
			OUT_REDIRECT = 1;
            		OUT_FILE = ARGS[i+1];
            		ARGS[i] = NULL;	
            		i+=2;
        	}
        	else if(strcmp(ARGS[i],">>")==0)
        	{
            		OUT_REDIRECT_APPEND = 1;
            		OUT_FILE = ARGS[i+1];
            		ARGS[i] = NULL;
            		i+=2;
        	}  
		else
            		i++;
	}
	/*end of redirect cmd*/
}

