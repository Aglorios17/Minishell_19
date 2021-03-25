/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aglorios <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:52:08 by aglorios          #+#    #+#             */
/*   Updated: 2021/03/09 15:03:34 by aglorios         ###   ########.fr       */
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
# include <term.h>
# include <termios.h>
# include "../libft/libft.h"

typedef struct	s_mini
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
	int			itrad;
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
}				t_shell;

typedef struct	s_sekot
{
	int			flagcs;
	int			i;
	int			len;
	int			a;
	char		*tmp;
	char		*tmp2;
}				t_sekot;

typedef struct	s_retok
{
	int			a;
	int			b;
	char		**trad;
	char		*backs;
	char		*first;
	char		*after;
	char		*tmp2;
	char		*env;
	int			adol;
	char		*new;
	int			count;
	char		*tmp;
}				t_retok;

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

typedef struct	s_signal
{
	int			prompt;
	int			pid;
	int			pid2;
	int			nc;
}				t_sign;

typedef struct termios	t_termios;

typedef struct	s_termcap
{
	int			len;
	int			i;
	int			y;
	int			a;
	char		*line;
	char		**history;
	int			fdhist;
	int			recupterm;
	char		*term;
	int			dist;
	int			cursor;
}				t_termcap;

t_termcap		*initglobalterm();

int				ft_putchar2(int c);
void			init_struct_tc(t_termcap *tc);
int				init_term(void);
char			**ft_split_line(char *line, char *line2);
char			**get_tab();
void			get_history(t_termcap *tc);
void			ft_write_in_history(t_termcap *tc);
void			ft_write_line(t_termcap *tc, char *str);
void			ft_key_backspace(t_termcap *tc);
void			ft_key_down(t_termcap *tc);
int				ft_newline_history(t_termcap *tc, char **add);
int				ft_key_up(t_termcap *tc, char **add);
int				ft_loop(t_termcap *tc, char **add, char *str);
char			*ft_termcap(t_shell *st);
char			*get_env_term(void);
void			default_term(void);

t_sign			*initglobal();

int				ft_tokens(t_shell *st);
int				ft_checkspace(char *line, t_sekot *sekot);
int				ft_cleantokens(t_shell *st);
char			*ft_traduction(t_shell *st, char *tmp);
int				ft_checkifsimplequote2(char *line, int i, int a);
int				ft_checkifsimplequote3(char *line, int i, t_sekot *sekot);
char			*ft_traduction4(t_shell *st, char *tmp, int b);
char			*ft_traduction5(t_shell *st, char *tmp);
char			*ft_traduction6(t_shell *st, char *tmp);
int				ft_simple_quote(t_shell *st, char *tmp, int a);
int				ft_double_quote(t_shell *st, char *tmp, int a);
int				ft_back(char *tmp, int a);

int				ft_command(t_shell *st);
int				ft_checkcommand(t_shell *st);
int				ft_echo(t_shell *st);
int				ft_exit(t_shell *st);
char			*ft_pwd(t_shell *st);
int				oldpwd(t_shell *st);

int				ft_cd(t_shell *st);
int				cdhomereturn(t_shell *st, char *line, char *tmp);
int				open_pathcd(t_shell *st, char *path);

int				ft_export(t_shell *st);
int				ft_export_noparam(t_shell *st);
int				ft_errornoval(t_shell *st, char *tmp);
int				ft_errorbefegal(t_shell *st, char *tmp);
int				ft_write_error(t_shell *st, char *tmp);
int				ft_exporterror(t_shell *st, char *tmp);

int				ft_unset(t_shell *st);

int				ft_envv(t_shell *st, char **envp);
int				ft_dollars(t_shell *st, char *tmp, int i);
void			freedol(t_dol *dol);
int				getvaluedol(t_shell *st, t_dol *dol);
int				ft_statusdol(t_shell *st, t_dol *dol);
int				ft_shlvldol(t_shell *st, t_dol *dol, char *tmp, int i);
int				goretokens(t_shell *st, t_dol *dol);
int				getafterdol(t_dol *dol, char *tmp, int i);

int				ft_retokens(t_shell *st, t_dol *dol);
int				ft_flagdq(t_shell *st, t_dol *dol, int a);
int				tradnull(t_shell *st, t_dol *dol, char **trad, int a);
int				readdtok(t_shell *st, t_dol *dol, char **trad, int a);
int				retok2first(t_shell *st, t_dol *dol, char **trad, int a);
int				retok2tradunnull(t_shell *st, t_dol *dol, char **trad);
int				retok2tok(t_shell *st, t_dol *dol, char **trad);
char			*retok2cafter(t_dol *dol, char **trad, int a);
char			*retokjoin(t_dol *dol, char **trad, int a);
int				retok2(t_shell *st, t_dol *dol, char **trad, int a);
int				spaceafter(t_shell *st, t_dol *dol, char **trad, int a);
int				retokspaceafter(t_shell *st, t_dol *dol, char **trad, int a);
int				switchretok(t_shell *st, t_dol *dol, char **trad, int a);

void			ft_init_retok(t_retok *retok, char *tmp, int i);
int				ft_dolredic(t_shell *st, char *tmp, int i);
void			ft_dolredir2(t_retok *retok, char *tmp);
int				ft_dolredir3(t_retok *retok, t_shell *st, char *tmp);
void			ft_dolredir4(t_retok *retok, t_shell *st, char *tmp);
void			ft_dolredir5(t_retok *retok, t_shell *st);
void			ft_dolredir6(t_retok *retok, t_shell *st, char *tmp);
void			ft_init_retok2(t_retok *retok, char *tmp);
int				ft_retokensrd(t_shell *st, char *lol, t_retok *retok);
int				ft_retokensrdpart2(t_retok *retok, t_shell *st);
void			ft_retokensrd2(t_retok *retok);
int				ft_retokensrd3(t_retok *retok, t_shell *st);
int				ft_retokensrd4(t_retok *retok, t_shell *st);
void			ft_retokensrd5(t_retok *retok, t_shell *st);
void			ft_retokensrd5_5(t_retok *retok, t_shell *st);
void			ft_retokensrd6(t_retok *retok, t_shell *st);
void			ft_retokensrd7(t_retok *retok, t_shell *st);
char			*ft_shlvl(char *line, int i);

int				ft_cutline(t_shell *st);
int				ft_cutpipe(t_shell *st);
char			**ft_splitms(char const *str, char c, t_shell *st);
int				ft_malloc_tab(char const *str, char c);
int				ft_malloc_tab2(char const *str, char c, int a);

int				ft_exec(t_shell *st);
char			*recupexp(t_shell *st);
void			ft_exec2(t_shell *st, int a, char **ar, char **en);
int				ft_error(t_shell *st);
int				ft_error2(t_shell *st, char *tmp, int i);
int				ft_error3(t_shell *st, char *tmp, int i);
int				ft_error4(t_shell *st, char *cmd);
int				check_path(t_shell *st, char *dollars);
char			**recuppath(t_shell *st, char **tabs);
int				open_pathcd(t_shell *st, char *path);
int				ft_directory_error(t_shell *st, int nb);
int				ft_directory_error2(t_shell *st, int nb);
int				ft_notfound_error(t_shell *st, int nb);
int				ft_permission_error(t_shell *st, int nb, char *str);

int				ft_redirections(t_shell *st);
int				ft_redirections_norme(t_shell *st);
t_list			*ft_redirections2(t_shell *st, char *supp, char *supp2,
				char *supp3);
int				ft_parse_redir(t_shell *st);
int				ft_parse_redir0(t_shell *st, int a);
void			ft_parse_redir2(t_shell *st, int a);
int				ft_parse_redir3(t_shell *st, int a);
int				ft_parse_redir4(t_shell *st, int a);
int				ft_check_redir(t_shell *st);
int				ft_check_errorredir(t_shell *st);
int				ft_check_errorredir2(char *tokens);
int				ft_check_errorredir3(char *tokens);
int				ft_check_errorredir4(char *tokens, char *tokensnext);
int				ft_check_errorredir5(char *tokensnext);
int				ft_check_errorredir6(char *tokens, char *tokensnext);
int				ft_isinstring(char *str, char c);

int				lstcmd(t_shell *st, char *line);
char			**ft_tabreturn(t_list *list);
void			ft_freetab(char **tabs);
int				ft_verif_syntax(t_shell *st);
int				ft_verif_syntax2(t_shell *st);
int				ft_skip_quotes(t_shell *st, int a);
int				ft_syntax_redir(t_shell *st, int a);
int				ft_syntax_redir2(t_shell *st, int a);
int				ft_syntax_redir3(t_shell *st, int a);
int				ft_syntax_semicolon(t_shell *st, int a);
int				ft_syntax_semicolon2(t_shell *st, int a);
int				ft_syntax_pipe(t_shell *st, int a);
int				ft_syntax_pipe2(t_shell *st, int a, int flagspace);
int				ft_syntax_pipe3(t_shell *st, int a, int flagspace);

void			signalhandler(int signum);
void			signalhandler2(int signum);
void			ft_init_struct(t_shell *st);
int				ft_pipe(t_shell *st);
int				mainprocess(t_shell *st);
int				commandline(t_shell *st);
t_shell			*globalstruct(void);

int				ft_free_end(t_shell *st);
int				ft_free_command(t_shell *st);
void			ft_free_list(t_list *list, t_list *first);

#endif
