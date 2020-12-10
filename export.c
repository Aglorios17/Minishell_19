#include "minishell.h"

int	ft_dollars(shell *st, char *tmp, int i)
{
	char *new;

	new = ft_strdup("");
	st->tmpq = ft_strdup("");
	i++;
	while (tmp[i] && (tmp[i] != '\'' || tmp[i] != '"' || tmp[i] != '\0'))
	{
		new = ft_charjoin(new, tmp[i]);
		i++;
	}
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
			i++;
			while (tmp[i] != '\0')
			{
				st->tmpq = ft_charjoin(st->tmpq, tmp[i]);
				i++;
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
	(void)envp;

	tmp = NULL;
	if (!st->tokens->next)
		return (0);
	st->tokens = st->tokens->next;
	tmp = (char *)st->tokens->content; 
//	printf("ok\n");
//	printf("tmp|%s|\n", tmp);
//	printf("tmp|%c|\n", tmp[i]);
//	printf("ok1\n");
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
	ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup(tmp)));
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
