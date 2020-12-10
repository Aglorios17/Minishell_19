#include "minishell.h"

char *ft_dollars(shell *st, char *tmp, int i)
{
	char *tok;
	char *tmp2;
	int	 a;

	tok = ft_strdup("");
	tmp2 = NULL;
	a = 0;
	i++;
	while (tmp[i])
	{
//		tmp2 = tok;
		tok = ft_charjoin(tok, tmp[i]);
//		free(tmp2);
		i++;
	}
	tmp2 = NULL;
	while (st->envv)
	{
		tmp2 = (char *)st->envv->content;	
		if (!ft_strncmp(tok, tmp2, ft_strlen(tok)))
		{
			a = 0;
			while(tmp2[a] && tmp2[a] != '=')
				a++;
			if (tmp2[a] == '=')
				a++;
//			printf("a|%i\n|", a);
//			printf("tmp2|%s|\n", tmp2);
			tok = ft_substr(tmp2, a, (ft_strlen(tmp2) - a));
//			printf("tok|%s|\n", tok);
//			free(tmp2);
			st->envv = st->firstenv;
			return (tok);
		}
		st->envv = st->envv->next;
	}
	tok = NULL;
	st->envv = st->firstenv;
	return (tok);
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
