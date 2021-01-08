#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include "libft/libft.h"

typedef struct	mini
{
	char		*line;
	char		*pwd;
	char		*oldpwd;
	char		*home;
	int			ret;
	int			status;
	int			quotes;
	int			quotes2;
	char		*new;
	char		*tmpq;
	char		*cmdexec;
	int			pass;
	int			flagdq;
	int			firstd;
	t_list		*tokens;
	t_list		*envv;
	t_list		*firsttok;
	t_list		*firstenv;
	t_list		*cutline;
	t_list		*firstcut;
}				shell;

//////////// tokens /////////////

int ft_tokens(shell *st);
int	ft_checkspace(char *line);
int ft_cleantokens(shell *st);
char *ft_clean_firsttoken(shell *st, char *tmp);
int ft_simple_quote(shell *st, char *tmp, int a);
int ft_double_quote(shell *st, char *tmp, int a);

/////////// command /////////////

int ft_command(shell *st, char **envp);
int	ft_checkcommand(shell *st);
int ft_echo(shell *st);
int ft_cd(shell *st);
char *ft_pwd(shell *st);

////////// export //////////////

int ft_export(shell *st, char **envp);
int ft_unset(shell *st);
int ft_envv(shell *st, char **envp);
int	ft_dollars(shell *st, char *tmp, int i);
char *ft_shlvl(char *line, int i);

////////// cut ////////////////

int ft_cutline(shell *st);
char **ft_splitms(char const *str, char c, shell *st);

////////// exec ////////////////

int ft_exec(shell *st);
int check_path(shell *st);

#endif
