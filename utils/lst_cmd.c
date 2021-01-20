#include "../include/minishell.h"

int lstcmd(shell *st, char *line)
{
	int i;
	int a;
	char *tmp;

	i = 0;
	a = 0;
	tmp = NULL;
	while (st->envv)
	{
		tmp = ft_strdup((char *)st->envv->content);
		if (!ft_strncmp(tmp, "=", 1))
			a = 1;
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (a == 1)
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	tmp = ft_strdup("");
	while (line[i] && line[i] != ' ')
	{
		tmp = ft_charjoin(tmp, line[i]);
		i++;
	}
//	tmp = ft_strdup("/home/user42/Bureau/minishell_test/bin/env");
//	printf("|%s|\n",tmp);
	a = 0;
	while (st->envv)
	{
		if (!ft_strcmp((char *)st->envv->content, ft_strjoin("_=", tmp)))
			a = 1;
		else if (!ft_strncmp((char *)st->envv->content, "_=", 2))
		{
			st->envv->content = ft_strjoin("_=", tmp);
			a = 1;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (a == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("_=", tmp)));
	st->envv = st->firstenv;
	return (1);
}
