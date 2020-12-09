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
	(void)envp;
	st->tokens = st->tokens->next;
	ft_lstadd_back(&st->envv, ft_lstnew(ft_strdup((char *)st->tokens->content)));
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
