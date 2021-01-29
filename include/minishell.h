#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libft/libft.h"
int prompt;
int pid;
int pid2;
int nc;

typedef struct	mini
{
	char		*line;
	char		*pwd;
	char		*pwdcp;
	char		*oldpwd;
	char		*home;
	char		*pat;
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
	int			ddone;
	int			pipefd;
	int			fdout;
	int			fdone;
	int			errorredir;
	int			rd;
	char		**redir;
	char		*redirnext;
	t_list		*tokens;
	t_list		*envv;
	t_list		*firsttok;
	t_list		*firstenv;
	t_list		*cutline;
	t_list		*firstcut;
	t_list		*pipe;
	t_list		*firstpipe;
	t_list		*redirection;
}				shell;

//////////// tokens /////////////

int ft_tokens(shell *st);
int	ft_checkspace(char *line);
int ft_cleantokens(shell *st);
char *ft_traduction(shell *st, char *tmp);
int ft_simple_quote(shell *st, char *tmp, int a);
int ft_double_quote(shell *st, char *tmp, int a);

/////////// command /////////////

int ft_command(shell *st, char **envp);
int	ft_checkcommand(shell *st);
int ft_echo(shell *st);
int ft_exit(shell *st);
char *ft_pwd(shell *st);
int oldpwd(shell *st);

/////////// cd //////////////////
int ft_cd(shell *st);
int	cdhomereturn(shell *st, char *line, char *tmp);
int	open_pathcd(shell *st, char *path);

////////// export //////////////

int ft_export(shell *st, char **envp);
int ft_unset(shell *st);
int ft_envv(shell *st, char **envp);
int	ft_dollars(shell *st, char *tmp, int i);
int	ft_dolredic(shell *st, char *tmp, int i);
char *ft_shlvl(char *line, int i);

////////// cut ////////////////

int ft_cutline(shell *st);
int ft_cutpipe(shell *st);
char **ft_splitms(char const *str, char c, shell *st);

////////// exec ////////////////

int ft_exec(shell *st);
int check_path(shell *st, char *dollars);
int open_pathcd(shell *st, char *path);

/////////// redirection ///////

int		ft_redirections(shell *st);
t_list	*ft_redirections2(shell *st, char *supp, char *supp2, char *supp3);
int		ft_parse_redir(shell *st, int fd);
int 	ft_check_redir(shell *st);
int 	ft_check_errorredir(shell *st);
int 	ft_check_errorredir2(shell *st);

/////////// utils /////////////

int statusenv(shell *st, int status);
t_list *lst_addin(char **tab, t_list *list, int i);
int	lstcmd(shell *st, char *line);
char **ft_tabreturn(t_list *list);
void    ft_freetab(char **tab);

/////////// main fonction /////////////
void ft_init_struct(shell *st);
int	ft_exfree(shell *st, t_list *tmp);
int	ft_exfree2(shell *st, t_list *tmp);
int	ft_freecutline(shell *st, t_list *tmp);
int	ft_freecutpipe(shell *st, t_list *tmp);

#endif
