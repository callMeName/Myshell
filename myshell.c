/*
 * Filename:myshell.c
T* Description: The main function of myshell
 * Author: Xu Yuhao
 * Created: 2014.7.30
 */
#include "myshell.h"

int main(void){
	int should_run = 1; /* flag to determine when to exit program */
	int i;
	for(i = 0; i < MAXCHILD;i ++)
		CHILDTABLE[i] = 0;
	while (should_run) 
	{
		printf("myshell>");
		fflush(stdout);
		/**
		* After reading user input, the steps are: 
		*Inner command：
		*…..
		*Out command：
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will invoke wait()
		*…..
		*/
		init_env();
		print_CMD();
		NUMBER_ARGS = get_args(); 	
		if(if_inner_cmd())
		{
			should_run = inner_pro();
		}
		else
		{
			if(NUMBER_ARGS > 1)
				out_parse();
			out_pro();			
		}
		clean();
	}
	return 0;
}
