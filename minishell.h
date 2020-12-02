#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
# include "libft/libft.h"

typedef struct	mini
{
	char		*line;
	char		*pwd;
	char		*home;
	int			ret;
	int			quotes;
	t_list		*tokens;
	t_list		*firsttok;
}				shell;

#endif
