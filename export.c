#include "minishell.h"

int ft_unset(shell *st)
{
	t_list *tmp;
	t_list *previous;
	char *un;

	tmp = NULL;
	previous = NULL;
	un = (char *)st->tokens->content;
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
		st->tokens = st->firsttok;
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
			st->tokens = st->firsttok;
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

int	ft_dollars(shell *st, char *tmp, int i)
{
	char *new;
	char *space;
	int  a;
	char **trad;

	new = ft_strdup("");
	st->pass = 0;
	trad = NULL;
	space = NULL;
	a = 0;
//	printf("tmp|%s|\n", tmp);
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
		if ((!ft_isalpha(tmp[i]) && !ft_isalpha(tmp[1])) && tmp[i] != '_')
			break;
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
			}
			else if (st->flagdq)
			{
				while (tmp[i])
				{
					st->tmpq = ft_charjoin(st->tmpq, tmp[i]);
					i++;
				}
			}
			else
			{
				trad = ft_split(&tmp[i], ' '); ////////////////////////////////// modif split
				i = 0;
				while (trad[i])
				{
					st->tmpq = ft_strjoin(st->tmpq, trad[i]);
					if (trad[i + 1])
						st->tmpq = ft_charjoin(st->tmpq, ' ');
					i++;
				}
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
	int p;
	int e;
	int s;
	char *tmp;
	
	a = 0;
	p = 0;
	e = 0;
	s = 0;
	tmp = NULL;
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
			s = 1;
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
		if (i != 0)
			a += 1;
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

	tmp = NULL;
	tmp2 = NULL;
	a = 0;
	i = 0;
	(void)envp;
//	if (!st->tokens->next)
//		return (0);
	if (!st->tokens->next) //////////////////////////////////////////////// faire avant trad (fonction) ou stocker l env dans un tableau avant trad
	{
		while (st->envv->next)
		{	
			tmp = ft_strdup("declare -x ");
			write(1, tmp, ft_strlen(tmp));
		//	tmp = ft_strjoin((char *)st->envv->content, "\n")); /////// mieux
		//	write(1, tmp, ft_strlen(tmp));
			tmp = ft_strdup((char *)st->envv->content); ////////// mouais
			i = 0;
			tmp2 = ft_strdup("");
			a = 0;
			while (tmp[i])
			{
//				printf("tmp|%c|\n", tmp[i]);
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
		tmp = (char *)st->tokens->content; 
//		printf("ok\n");
//		printf("tmp|%s|\n", tmp);
//		printf("tmp|%c|\n", tmp[i]);
//		printf("ok1\n");
		if (ft_isdigit(tmp[0]) || ft_strchr(tmp, '\\') || ft_strchr(tmp, '\'') || ft_strchr(tmp, '"') || ft_strchr(tmp, '$') || ft_strchr(tmp, '|') || ft_strchr(tmp, ';') || ft_strchr(tmp, '&') || ft_strchr(tmp, '!') ||  ft_strchr(tmp, '@'))
		{
			write(1, "minishell: export: `", 20);
			write(1, tmp, ft_strlen(tmp));
			write(1, "': not a valid identifier\n", 26);
			st->status = 1;
			return (0);
		}
		if (!ft_strchr(tmp, '='))
			return (0);
		a = 0;
		while (tmp[a] != '=') ////////////////////////////////////// export lol =mdr (parser)
			a++;
		if (tmp[a] == '=' && tmp[a - 1] == ' ')
		{
			write(1, "minishell: export: `", 20);
			write(1, tmp, ft_strlen(tmp));
			write(1, "': not a valid identifier\n", 26);
			st->status = 1;
			return (0);
		}
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
//					printf("envv|%s|\n", (char *)st->envv->content);
				}
				else
					st->envv->content = ft_strdup(tmp);
				a = 1;
			}
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
		if (a == 0)
			ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup(tmp)));
		st->tokens = st->tokens->next;
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
