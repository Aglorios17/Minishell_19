/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:52:08 by aglorios          #+#    #+#             */
/*   Updated: 2020/03/04 12:53:38 by aglorios         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int			itrad;                   //// norme trad
	int			fdredir;
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

typedef struct	s_sekot
{
	int			flagcs;
	int			i;
	int			len;
	int			a;
	char		*tmp;
	char		*tmp2;
}				t_sekot;

typedef struct	s_dol
{
	int			cafter;
	char		*nw;
	char		*first;
	char		*after;
	char		*env;
	char		*backs;
	t_list		*nex;
}				t_dol;
//////////// tokens /////////////

int ft_tokens(shell *st);
int	ft_checkspace(char *line, t_sekot *sekot);
int ft_cleantokens(shell *st);
char *ft_traduction(shell *st, char *tmp);
int	ft_checkifsimplequote2(char *line, int i, int a);
int	ft_checkifsimplequote3(char *line, int i, t_sekot *sekot);
char	*ft_traduction4(shell *st, char *tmp, int b);
char	*ft_traduction5(shell *st, char *tmp);
char	*ft_traduction6(shell *st, char *tmp);
int ft_simple_quote(shell *st, char *tmp, int a);
int ft_double_quote(shell *st, char *tmp, int a);
int	ft_back(char *tmp, int a);

/////////// command /////////////

int ft_command(shell *st);
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

int ft_export(shell *st);
int ft_export_noparam(shell *st);
int	ft_errornoval(shell *st, char *tmp);
int	ft_errorbefegal(shell *st, char *tmp);
int	ft_write_error(shell *st, char *tmp);
int	ft_exporterror(shell *st, char *tmp);


////////// unset //////////////

int ft_unset(shell *st);

////////// envv //////////////

int ft_envv(shell *st, char **envp);
int	ft_dollars(shell *st, char *tmp, int i);
void	freedol(t_dol *dol);
int	getvaluedol(shell *st, t_dol *dol);
int	ft_statusdol(shell *st, t_dol *dol);
int	ft_shlvldol(shell *st, t_dol *dol, char *tmp, int i);
int	goretokens(shell *st, t_dol *dol);
int	getafterdol(t_dol *dol, char *tmp, int i);
//////////// retokens ///////////
int	ft_retokens(shell *st, t_dol *dol);
int	ft_flagdq(shell *st, t_dol *dol, int a);
int	tradnull(shell *st, t_dol *dol, char **trad, int a);
int	readdtok(shell *st, t_dol *dol, char **trad, int a);
int	retok2first(shell *st, t_dol *dol, char **trad, int a);
int	retok2tradunnull(shell *st, t_dol *dol, char **trad);
int	retok2tok(shell *st, t_dol *dol, char **trad);
char	*retok2cafter(t_dol *dol, char **trad, int a);
char	*retokjoin(t_dol *dol, char **trad, int a);
int	retok2(shell *st, t_dol *dol, char **trad, int a);
int	spaceafter(shell *st, t_dol *dol, char **trad, int a);
int		retokspaceafter(shell *st, t_dol *dol, char **trad, int a);
int	switchretok(shell *st, t_dol *dol, char **trad, int a);


//////////// retokens ///////////
int	ft_dolredic(shell *st, char *tmp, int i);
int	ft_retokensrd(shell *st, char *env, char *first, char *after, char *tmp);
char *ft_shlvl(char *line, int i);

////////// cut ////////////////

int ft_cutline(shell *st);
int ft_cutpipe(shell *st);
char **ft_splitms(char const *str, char c, shell *st);
int	ft_malloc_tab(char const *str, char c);
int	ft_malloc_tab2(char const *str, char c, int a);

////////// exec ////////////////

int 	ft_exec(shell *st);
char	*recupexp(shell *st);
void	ft_exec2(shell *st, int a, char **ar, char **en);
int		ft_error(shell *st, struct stat b);
int		ft_error2(shell *st, char *tmp, int i, struct stat b);
int		ft_error3(shell *st, char *tmp, int i, struct stat b);
int		ft_error4(shell *st, char *cmd, struct stat b);
int 	check_path(shell *st, char *dollars);
char	**recuppath(shell *st, char **tab);
int 	open_pathcd(shell *st, char *path);
int		ft_directory_error(shell *st, int nb);
int		ft_directory_error2(shell *st, int nb);
int		ft_notfound_error(shell *st, int nb);
int		ft_permission_error(shell *st, int nb, char *str);

/////////// redirections ///////

int		ft_redirections(shell *st);
int		ft_redirections_norme(shell *st);
t_list	*ft_redirections2(shell *st, char *supp, char *supp2, char *supp3);
int		ft_parse_redir(shell *st);
int		ft_parse_redir0(shell *st, int a);
void	ft_parse_redir2(shell *st, int a);
int		ft_parse_redir3(shell *st, int a);
int		ft_parse_redir4(shell *st, int a);
int		ft_check_redir(shell *st);
int		ft_check_errorredir(shell *st);
int		ft_check_errorredir2(char *tokens);
int		ft_check_errorredir3(char *tokens);
int		ft_check_errorredir4(char *tokens, char *tokensnext);
int		ft_check_errorredir5(char *tokensnext);
int		ft_check_errorredir6(char *tokens, char *tokensnext);
int		ft_isinstring(char *str, char c);

/////////// utils /////////////

int		lstcmd(shell *st, char *line);
char	**ft_tabreturn(t_list *list);
void	ft_freetab(char **tab);
int		ft_verif_syntax(shell *st);
int		ft_verif_syntax2(shell *st);
int		ft_skip_quotes(shell *st, int a);
int 	ft_syntax_redir(shell *st, int a);
int		ft_syntax_redir2(shell *st, int a);
int		ft_syntax_redir3(shell *st, int a);
int		ft_syntax_semicolon(shell *st, int a);
int		ft_syntax_semicolon2(shell *st, int a);
int		ft_syntax_pipe(shell *st, int a);
int		ft_syntax_pipe2(shell *st, int a, int flagspace);
int		ft_syntax_pipe3(shell *st, int a, int flagspace);

/////////// main fonction /////////////
void	signalhandler(int signum);
void	signalhandler2(int signum);
void	ft_init_struct(shell *st);
int		ft_pipe(shell *st);
int		mainprocess(shell *st);
int		commandline(shell *st);
////////////// free ////////////////
int		ft_free_end(shell *st);
int		ft_free_command(shell *st);
void	ft_free_list(t_list *list, t_list *first);

#endif
