#include "../include/minishell.h"

int lstcmd(shell *st, char *line)
{
	int i;
	int a;
	char *tmp;
	char *tmp2;
	char *fri;

	i = 0;
	a = 0;
	tmp = NULL;
	tmp2 = NULL;
	fri = NULL;
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
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
		fri = tmp;
		tmp = ft_charjoin(tmp, line[i]); ///////////////////// free
		free(fri);
		i++;
	}
	a = 0;
	free(tmp2);
	tmp2 = NULL;
	tmp2 = ft_strjoin("_=", tmp); //////////// free
	while (st->envv)
	{
		if (!ft_strcmp((char *)st->envv->content, tmp2))
			a = 1;
		else if (!ft_strncmp((char *)st->envv->content, "_=", 2))
		{
			free(st->envv->content);
			st->envv->content = NULL;
			st->envv->content = ft_strdup(tmp2);
			a = 1;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (a == 0)
		ft_lstadd_back(&st->envv, ft_lstnew("_=/bin/bash"));                 ////// free ft_strjoin
	st->envv = st->firstenv;
	free(tmp);
	free(tmp2);
	return (1);
}
