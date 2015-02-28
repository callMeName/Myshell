/*
 * Filename: utility.c
 * Description: The utility functions of myshell.
 * Author: Xu Yuhao
 * Created: 2014.7.30
 */

#include "myshell.h"

char* inner_cmd[7]={"cd","clr","dir","environ","echo","help","quit"};
void init_env()
{
	int i;
	for(i = 0; i < MAX_LINE / 2 + 1; i ++)
		ARGS[i] = (char*)malloc(sizeof(char)*30);
	NUMBER_ARGS = 0;
	IN_FILE = NULL;
	OUT_FILE = NULL;
	BACKGROUND = 0;
	IN_REDIRECT = 0;
	OUT_REDIRECT = 0;
	OUT_REDIRECT_APPEND = 0;
	PATH = getenv("PATH");
}

void print_CMD()
{
	char *CMD = (char *)malloc(sizeof(char)*100);
	char *username = (char *)malloc(sizeof(char)*20);
	char *path = (char *)malloc(sizeof(char)*50);
	if(CMD == NULL || username == NULL || path == NULL)
    	{
       		printf("Myshell error:malloc failed.\n");
        	return;
    	}
	getcwd(path,50);
	strcpy(username,getlogin());
	add_env_PATH(path);
	pwd = getpwuid(getuid());
	strcpy(CMD,"[");
	strcat(CMD,username);
	strcat(CMD,"@localhost ");
        /*If path is including the home path then replace it by "~"*/
	if(strlen(path) < strlen(pwd->pw_dir) || strncmp(path,pwd->pw_dir,strlen(pwd->pw_dir))!=0)
                sprintf(CMD+strlen(CMD),"%s",path);
        else
                sprintf(CMD+strlen(CMD),"~%s",path+strlen(pwd->pw_dir));
	strcat(CMD,"]$");
	printf("%s ",CMD);
	fflush(stdout);
	free(CMD);
	free(username);
	free(path);
}

void add_env_PATH(char * which_to_add)
{
	char * new_PATH = (char *)malloc(strlen(which_to_add) + strlen(PATH) +40);
	strcpy(new_PATH,PATH);
	strcat(new_PATH,":");
	strcat(new_PATH,which_to_add);
	setenv("PATH",new_PATH,1);
	free(new_PATH);
}

int get_args()
{
	char ch;
	char temp[30];
	int i = 0, j = 0;
	ch = getchar();
	if(ch == '\n')
		return 0;
	while(ch != '\n')
	{
		if(ch != ' ')
			temp[j++] = ch;
		else
		{
			temp[j] = '\0'; //the end of an array
			if(strlen(temp) > 0)
			{
				strcpy(ARGS[i],temp);
				i++;
				j = 0;
			}
		}
		
		ch = getchar();
	}
	temp[j] = '\0';
	if(strlen(temp) > 0)
	{
		strcpy(ARGS[i],temp);
		i++;
		j=0;
	}
	/*free the extra ARGS*/
	for(j = i;j < MAX_LINE/2+1; j++)
	{
		free(ARGS[j]);
		ARGS[j] = NULL; 
	}
	return i;	
}


int if_inner_cmd()
{
	int i;
	int flag_inner = 0; /*flag of inner cmd*/
	for(i = 0;i < 7;i ++)
	{
		if(strcmp(ARGS[0],inner_cmd[i]) == 0)
		{
			flag_inner = 1;
			break;
		}
	}
	return flag_inner;
}

void change_direct()
{
	int fd_in,fd_out;
	/*redirect the stdin or stdout*/
	if(OUT_REDIRECT)
        {
	      fd_out = open(OUT_FILE, O_WRONLY|O_CREAT|O_TRUNC, 0666);
              close(fileno(stdout));
              dup2(fd_out, fileno(stdout));
              close(fd_out);
         }
         if(OUT_REDIRECT_APPEND)
         {
              fd_out = open(OUT_FILE, O_WRONLY|O_APPEND, 0666);
              close(fileno(stdout));
              dup2(fd_out, fileno(stdout));
              close(fd_out);
         }
         if(IN_REDIRECT)
         {
              fd_in = open(IN_FILE, O_CREAT |O_RDONLY, 0666);
              close(fileno(stdin));
              dup2(fd_in, fileno(stdin));
              close(fd_in);
         }

}

void clean()
{
	int i;
	for(i = 0; i < NUMBER_ARGS; i ++)
		if(ARGS[i] != NULL)
		{
			free(ARGS[i]);
		}
	setenv("PATH",PATH,1); // return the foreign PATH
}




