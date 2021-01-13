#include "minishell.h"

int ft_unset(shell *st)
{
	t_list *tmp;
	t_list *previous;
	char *un;

	tmp = NULL;
	previous = NULL;
	un = (char *)st->tokens->content;
//	printf("tokens|%s|\n", un);
	if (!ft_strncmp(un, "PWD\0", ft_strlen(un)))
		st->pwd = ft_strdup("");
	if (!ft_strncmp(un, "PATH\0", ft_strlen(un)))
		st->pat = NULL;
	if (un[0] == '\0')
	{
		write(1, "minishell: unset: `", 19);
		write(1, "': not a valid identifier\n", 26);
		if (!ft_strchr(un, ' '))
			st->status = 1;
		return (0);
	}
	if (ft_strchr(un, '=') || ft_strchr(un, ' '))
	{
		write(1, "minishell: unset: `", 19);
		write(1, un, ft_strlen(un));
		write(1, "': not a valid identifier\n", 26);
		if (!ft_strchr(un, ' '))
			st->status = 1;
		return (0);
	}
	un = ft_charjoin(un, '=');
	previous = st->envv;
	if (!ft_strncmp(un, (char *)previous->content, ft_strlen(un)))
	{
		st->envv = previous->next;
		free(previous);
		st->firstenv = st->envv;
	//	st->tokens = st->firsttok;
		return (0);
	}
	previous = st->envv;
	tmp = previous->next;
	while (tmp)
	{
		if (!ft_strncmp(un, (char *)tmp->content, ft_strlen(un)))
		{
			previous->next = tmp->next;
			free(tmp);
			st->envv = st->firstenv;
	//		st->tokens = st->firsttok;
			return (0);
		}
		previous = tmp;
		tmp = tmp->next;
	}
	st->envv = st->firstenv;
	return (0);
}

/*
char *ft_pass_space(char *tmp, int i)
{
	char *new;
	int a;

	a = i + 1;
	new = ft_strdup("");
	while (tmp[i] == ' ')
		i++;
	if (tmp[i] == '\0')
	{
		i = 0;
		while (tmp[i] <= a)
		{
			new = ft_charjoin(new, tmp[i]);
			i++;
		}
		new = ft_charjoin(new, ' ');
		return (new);
	}
	return (tmp);
}
*/
int	ft_cmddollars(shell *st, char *tmp)
{
	if (check_path(st, tmp) == 1)
		return (1);
	if (!ft_strcmp(tmp, "echo") || !ft_strcmp(tmp, "cd") || !ft_strcmp(tmp, "pwd") ||
		!ft_strcmp(tmp, "env") || !ft_strcmp(tmp, "export") ||
		!ft_strcmp(tmp, "unset") || !ft_strcmp(tmp, "exit") || !ft_strcmp(tmp, "exec"))
	{
		return (1);
	}
	else
		return (0);
}


int	ft_dollars(shell *st, char *tmp, int i)
{
	char	*new;
	char	*space;
	int 	a;
	int		b;
	int		c;
	char	*tmp2;
	char	*trad; //////////////////////// changer trad char * (nouv)/ char **
	char	*first;
	char	*val;

	new = ft_strdup("");
	st->pass = 0;
	trad = NULL;
	space = NULL;
	first = NULL;
	val = NULL;
	(void)tmp2;
	(void)trad;
	(void)first;
	a = 0;
	b = 0;
	c = 0;
	(void)b;
	(void)val;
	tmp2 = tmp;
//	printf("tmp2 : |%s|\n", tmp2);
	val = ft_strdup(&tmp[i - 1]);
	if (tmp[i + 1] == '\0' || tmp[i + 1] == '\\')
	{
		st->tmpq = ft_charjoin(st->tmpq, '$');
		st->pass = i;
		return (0);
	}
	i++;
//	printf("tmp|%c|\n", tmp[1]);
	while (tmp[i] && !ft_strchr("\'\"", tmp[i]) && tmp[i] != '\0')
	{
//		printf("tmp[1] : |%c|\n", tmp[1]);
//		printf("tmp[i] : |%c|\n", tmp[i]);
		if (!ft_isalnum(tmp[i]) && tmp[i] != '_')
		{
//			printf("OK\n");
			break;
		}
		if (tmp[i] == '$' || tmp[i] == '\\') /////////////////////////////////////////////////////////// 
		{
			if (tmp[i] == '\\' && !tmp[i + 1])
				space = ft_strdup(" ");
			break;
		}
		new = ft_charjoin(new, tmp[i]);
//		printf("join|%s|\n", new);
		i++;
	}
//	printf("new|%s|\n", new);
	st->pass = i - 1;
	new = ft_charjoin(new, '=');
//	printf("new|%s|\n", new);
	tmp = NULL;
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
//		printf("tmp|%s|\n", tmp);
		if (!ft_strncmp(new, tmp, ft_strlen(new)))
		{
			i = 0;
			while (tmp[i] && tmp[i] != '=')
				i++;
			if (tmp[i] == '=')
				i++;
//			tmp = ft_pass_space(tmp, i);
			if (!ft_strncmp(tmp, "SHLVL=", i))
			{
//				printf("ok\n");
				a = ft_atoi(&tmp[i]);
				st->tmpq = ft_strdup(&ft_shlvl(&tmp[i], a)[6]);	
//				printf("envv|%s|\n", (char *)st->envv->content);
			}///* //////////////////////////////////////////////////////////////////////////////////// debut nouv
			else
			{
//				printf("ok\n");
				(void)tmp2;
				(void)first;
//				printf("&tmp[i] : |%s|\n", &tmp[i]);
//				printf("tmp2 : |%s|\n", tmp2);
//				printf("flag : |%i|\n", st->flagdq);
				first = ft_substr(tmp2, st->pass + 1, ft_strlen(tmp2));
				trad = ft_strdup(&tmp[i]);
//				printf("first : |%s|\n", first);
//				printf("tmp : |%s|\n", tmp);
//				printf("trad1 : |%s|\n", trad);
//				printf("val : |%s|\n", val);
				a = 0;
				b = 0;
				while (trad[a] && trad[a] == ' ')
					a++; 
				if (trad[a] != '\0' && st->flagdq == 1)
					c = 1;
//				printf("trad[a] : |%c|\n", trad[a]);
				else if (trad[a] != '\0')
				{
//					if (!ft_strncmp(trad, "echo", 5) || !ft_strncmp(trad, "cd", 3) ||
//						!ft_strncmp(trad, "pwd", 4) ||
//						!ft_strncmp(trad, "env", 4) || !ft_strncmp(trad, "export", 7) ||
//						!ft_strncmp(trad, "unset", 6) || !ft_strncmp(trad, "exit", 5))
//					{
//						printf("ok\n");
//					//	st->envv = st->firstenv;
					//	return (ft_strlen(st->tmpq));
//					}
					if (trad[a] != '\0')
					{
						tmp = ft_strdup("");
						while (trad[a])
						{
//							printf("trad[a]bcl : |%c|\n", trad[a]);
							if (trad[a] == ' ' && (trad[a + 1] == ' ' || trad[a + 1] == '\0'))
								a++;
							else
							{
								tmp = ft_charjoin(tmp, trad[a]);
								a++;
							}
						}
						i = 0;
					}
				}
				else if (trad[a] == '\0')
				{
//					printf("trad[a] : |%c|\n", trad[a]);
					if (st->flagdq == 1)
					{
//						printf("trad2 : |%s|\n", trad);
						tmp = ft_strdup(trad);
					}
					else if (st->flagdq == 0 && tmp2[0] != '$' && first[0])
						tmp = ft_strdup(" ");
					else
						tmp = ft_strdup("");
					i = 0;
					b = 1;
				}
//				printf("tmp2[0] : |%c|\n", tmp2[0]);
//				printf("first[0] : |%c|\n", first[0]);
//				printf("tmpfin trad : |%s|\n", tmp);
				while (tmp[i])
				{
					st->tmpq = ft_charjoin(st->tmpq, tmp[i]);
					i++;
				}
//				printf("firstd : |%i|\n", st->firstd);
			//	if (trad[0] == ' ' && st->firstd > 2)
			//		st->tmpq = ft_strjoin(" ", st->tmpq);
				if (trad[ft_strlen(trad) - 1] == ' ' && (first[0] && first[0] != '$') && b == 0 && c== 0)
					st->tmpq = ft_charjoin(st->tmpq, ' ');
				if (trad[0] == ' ' && val[0] && b == 0 && c == 0)
					st->tmpq = ft_strjoin(" ", st->tmpq);
	//			printf("tmpqfin : |%s|\n", st->tmpq);
			}
//			printf("st->tmpq|%s|\n", st->tmpq);
			if (space)
				st->tmpq = ft_charjoin(st->tmpq, ' ');
			st->envv = st->firstenv;
			return (ft_strlen(st->tmpq));
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (!ft_strncmp("$OLDPWD", tmp2, 7))
	{
//		printf("okok\n");
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("OLDPWD=", "")));
	}
	st->envv = st->firstenv;
	return (ft_strlen(new));
}

int	ft_cutline(shell *st)
{
	int a;
	char **line;
	a = 0;
	line = ft_splitms(st->line, ';', st);
	while (line[a])
	{
		ft_lstadd_back(&st->cutline, ft_lstnew(ft_strdup(line[a])));
		a++;
	}
//	printf("envv1|%s|\n", (char *)st->envv->content);
	st->firstcut = st->cutline;
/*
	while (st->cutline != NULL)
	{
		printf("cut|%s|\n", (char *)st->cutline->content);
		st->cutline = st->cutline->next;
	}
	st->cutline = st->firstcut;
*/
    return (0);
}

int	ft_envv(shell *st, char **envp)
{
	int a;
	int i;
	int p;
	int e;
	int s;
	char *tmp;
	int num;
	
	a = 0;
	p = 0;
	e = 0;
	s = 0;
	tmp = NULL;
	num = 0;
	i = 0;
//	printf("envv1|%s|\n", (char *)st->envv->content);
//	printf("ok\n");
	while (envp[a])
	{
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup(envp[a])));
		a++;
	}
	st->firstenv = st->envv;
	st->envv = st->firstenv;
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(tmp, "PWD", 3))
			p = 1;
		if (!ft_strncmp(tmp, "_", 1))
			e = 1;
		if (!ft_strncmp(tmp, "SHLVL", 5))
		{
			i = 0;
			while (tmp[i] && tmp[i] != '=')
				i++;
			if (tmp[i] && tmp[i] == '=')
				i++;
			num = ft_atoi(&tmp[i]) + 1;
			st->envv->content = ft_strjoin("SHLVL=", ft_itoa(num));
			s = 1;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
//	printf("_|%i|\n", e);
//	printf("s|%i|\n", s);
	if (p == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("PWD=", ft_pwd(st))));
	if (s == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup("SHLVL=1")));
	if (e == 0)
		(void)st;
	st->envv = st->firstenv;
/*
	while (st->envv != NULL)
	{
		printf("envv|%s|\n", (char *)st->envv->content);
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
*/
    return (0);
}

char *ft_shlvl(char *line, int i)
{
	int a;

	a = 0;
//	printf("i|%i|\n", i);
//	printf("line |%s|\n", line);
	if (!ft_atoi(line))
		a = 1;
	else
	{
		a = ft_atoi(line);
		(void)i;
//		if (i != 0)
//			a += 1;
	}
	if (a < 0)
		a = 0;
	if (a >= 1000)
	{
		write(1, "minishell: warning: shell level (", 33);	
		write(1, ft_itoa(a), ft_strlen(ft_itoa(a)));
		write(1, ") too high, resetting to 1\n", 27);	
		a = 1;
	}
//	printf("level |%i|\n", a);
	line = ft_itoa(a);
	line = ft_strjoin("SHLVL=", line);
//	printf("line |%s|\n", line);
	return (line);
}

int ft_export(shell *st, char **envp)
{
	char *tmp;
	char *tmp2;
	int	a;
	int	i;
	int err;

	tmp = NULL;
	tmp2 = NULL;
	a = 0;
	err = 0;
	i = 0;
	(void)envp;
//	if (!st->tokens->next)
//		return (0);
	if (!st->tokens->next)
	{
		while (st->envv->next)
		{	
			tmp = ft_strdup("declare -x ");
			write(1, tmp, ft_strlen(tmp));
			tmp = ft_strdup((char *)st->envv->content);
			i = 0;
			tmp2 = ft_strdup("");
			a = 0;
			while (tmp[i])
			{
//				printf("tmp|%c|\n", tmp[i]);
				if (ft_strchr("\\\"$", tmp[i]))
					tmp2 = ft_charjoin(tmp2, '\\');
				tmp2 = ft_charjoin(tmp2, tmp[i]);
				if (tmp[i] == '=' && !a)
				{
					tmp2 = ft_charjoin(tmp2, '"');
					a = 1;
				}
				i++;
				if (tmp[i] == '\0')
					tmp2 = ft_charjoin(tmp2, '"');
			}
			tmp2 = ft_strjoin(tmp2, "\n");
			i = 0;
			write(1, tmp2, ft_strlen(tmp2));
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
		return (0);
	}
	st->tokens = st->tokens->next;
	while (st->tokens)
	{
		err = 0;
		tmp = (char *)st->tokens->content; 
//		printf("ok\n");
	//	printf("tmp|%s|\n", tmp);
//		printf("tmp|%c|\n", tmp[i]);
//		printf("ok1\n");
		if (tmp[0] == '\0')
		{
		
			write(1, "minishell: export: `", 20);
			write(1, "': not a valid identifier\n", 26);
			st->status = 1;
			err = 1;
		}
		if (((!ft_strchr(tmp, '=') && ft_strchr(tmp, ' ')) || tmp[0] == '=') && err == 0)
		{
			write(1, "minishell: export: `", 20);
			write(1, tmp, ft_strlen(tmp));
			write(1, "': not a valid identifier\n", 26);
			st->status = 1;
			err = 1;
		}
		if (err == 0)
		{
			if (ft_isdigit(tmp[0]) || ft_strchr(tmp, '\\') || ft_strchr(tmp, '\'') || ft_strchr(tmp, '"') || ft_strchr(tmp, '$') || ft_strchr(tmp, '|') || ft_strchr(tmp, ';') || ft_strchr(tmp, '&') || ft_strchr(tmp, '!') ||  ft_strchr(tmp, '@'))
			{
				write(1, "minishell: export: `", 20);
				write(1, tmp, ft_strlen(tmp));
				write(1, "': not a valid identifier\n", 26);
				st->status = 1;
				err = 1;
	//			return (0);
			}
		}
		if (!ft_strchr(tmp, '=') && err == 0)
			err = 1;
//			return (0);
		a = 0;
		while (tmp[a] != '=' && err == 0) ////////////////////////////////////// export lol =mdr (parser)
		{
			if (tmp[a] == ' ')
			{
				write(1, "minishell: export: `", 20);
				write(1, tmp, ft_strlen(tmp));
				write(1, "': not a valid identifier\n", 26);
				st->status = 1;
				err = 1;
			}
			a++;
		}
		if (tmp[a] == '=' && tmp[a - 1] == ' ' && err == 0)
		{
			write(1, "minishell: export: `", 20);
			write(1, tmp, ft_strlen(tmp));
			write(1, "': not a valid identifier\n", 26);
			st->status = 1;
			err = 1;
		//	return (0);
		}
		if (err == 1)
			st->tokens = st->tokens->next;
		if (err == 0)
		{
			a = 0;
			while (st->envv != NULL)
			{
				tmp2 = (char *)st->envv->content;
				i = 0;
				while (tmp2[i] != '=')
					i++;
				if (tmp2[i] == '=')
					i++;
				if (!ft_strncmp(tmp, tmp2, i))
				{
					if (!ft_strncmp(tmp, "SHLVL=", i))
					{
						a = ft_atoi(&tmp2[i]);
				//		printf("ok\n");
						st->envv->content = ft_shlvl(&tmp[i], a);	
//						printf("envv|%s|\n", (char *)st->envv->content);
					}
					else
					{
						if (!ft_strncmp(tmp, "PWD=", i))
							st->pwd = ft_strdup(&tmp[i]);		
						if (!ft_strncmp(tmp, "OLDPWD=", i))
							st->oldpwd = ft_strdup(&tmp[i]);		
						st->envv->content = ft_strdup(tmp);
					}
					a = 1;
				}
				st->envv = st->envv->next;
			}	
			st->envv = st->firstenv;
			if (a == 0)
				ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup(tmp)));
			st->tokens = st->tokens->next;
		}
	}
	st->tokens = st->firsttok;
/*
	while (st->envv != NULL)
	{
		printf("envv|%s|\n", (char *)st->envv->content);
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
*/
    return (0);
}
