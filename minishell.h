#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "libft/libft.h"

typedef struct	mini
{
	char *line;
	char *pwd;
	int ret;
}		shell;

#endif
