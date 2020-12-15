#include "minishell.h"

int ft_unset(shell *st)
{
	t_list *tmp;
	t_list *previous;
	char *un;

	tmp = NULL;
	previous = NULL;
	un = (char *)st->tokens->next->content;
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
	st->tokens = st->firsttok;
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
	int a;
	int b;

	new = ft_strdup("");
	st->pass = 0;
	a = 0;
	b = 0;
//	if (tmp[i - 1])
//		a = 1;
	if (tmp[i + 1] == '\0' || tmp[i + 1] == '\\')
	{
		st->tmpq = ft_charjoin(st->tmpq, '$');
		st->pass = i;
		return (0);
	}
	i++;
	b = i;
	while (tmp[i] && !ft_strchr("\'\"", tmp[i]) && tmp[i] != '\0')
	{
		if (!ft_isalpha(tmp[i]))
			break;
		new = ft_charjoin(new, tmp[i]);
		i++;
	}
//	printf("new|%s|\n", new);
//	printf("tmp|%s|\n", &tmp[b]);
	if (ft_strlen(new) == ft_strlen(&tmp[b]))
		a = 1;
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
			while (st->flagdq == 1 && tmp[i] == ' ') ////////// wtf diff a==0 et a==1
					i++;
			while (tmp[i])
			{
				if (a == 1 && st->flagdq == 1 && (tmp[i] == ' ' && (tmp[i + 1] == ' ' || tmp[i + 1] == '\0')))
					i++;
				else
				{
					st->tmpq = ft_charjoin(st->tmpq, tmp[i]);
					i++;
				}
			}
		//	printf("st->tmpq|%s|\n", st->tmpq);
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

	line = ft_split(st->line, ';');
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
	
	a = 0;
	while (envp[a])
	{
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup(envp[a])));
		a++;
	}
//	printf("envv1|%s|\n", (char *)st->envv->content);
	st->firstenv = st->envv;
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
	if (!st->tokens->next)
		return (0);
	st->tokens = st->tokens->next;
	while (st->tokens)
	{
		tmp = (char *)st->tokens->content; 
//		printf("ok\n");
//		printf("tmp|%s|\n", tmp);
//		printf("tmp|%c|\n", tmp[i]);
//		printf("ok1\n");
		if (ft_strchr(tmp, '\\') || ft_strchr(tmp, '\'') || ft_strchr(tmp, '"') || ft_strchr(tmp, '$') || ft_strchr(tmp, '|') || ft_strchr(tmp, ';') || ft_strchr(tmp, '&') || ft_strchr(tmp, '!') ||  ft_strchr(tmp, '@'))
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
