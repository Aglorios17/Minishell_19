#include "../include/minishell.h"

int statusenv(shell *st, int status)
{
	char	*env;
	int		i;

	env = NULL;
	i = 0;
//	printf("status|%i|\n" , status);
	while (st->envv)
	{
		env = ft_strdup((char *)st->envv->content);
		if (!ft_strncmp(env, "?=", 2))
		{
			i = 0;
			while (env[i] && env[i] != '=')
				i++;
			if (env[i] && env[i] == '=')
				i++;
			st->envv->content = ft_strjoin("?=", ft_itoa(status));
			st->envv = st->firstenv;
			return (status);
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
//	printf("|%s|\n" ,ft_strjoin("?=", ft_itoa(status)));
	ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("?=", ft_itoa(status))));
	st->envv = st->firstenv;
	return (status);
}
