#include "../include/minishell.h"

void signalhandler(int signum)
{
//	printf("\npid|%i|\n", pid);
	(void)signum;
	if (pid == 0)
	{
		kill(0, 0);
		pid = 1;
		pid2 = 0;
	}
	else
	{
		if (nc == 0)
			write(2,"\n>>",3);
		else
			write(2,"\n",1);
		nc = 0;
		prompt = 1;
	}
//	printf("pid2|%i|\n", pid);
}

void signalhandler2(int signum)
{
	(void)signum;
//	printf("\npid2|%i|\n", pid2);
	if (pid2 > 0)
	{
		kill(0, 0);
		write(2,"\nCORE DUMP CONNARD",18);
		if (nc == 0)
			write(2,"\n>>",3);
		else
			write(2,"\n",1);
		prompt = 1;
		pid2 = 0;
	}
	else
	{
		if (nc == 0)
			write(2,"\n>>",3);
		else
			write(2,"\n",1);
		nc = 0;
		prompt = 1;
	}
//	printf("pid2|%i|\n", pid);
}
