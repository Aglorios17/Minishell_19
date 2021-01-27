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
	fri = NULL;
	tmp2 = NULL;
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
		tmp = ft_charjoin(tmp, line[i]);
		free(fri);
		i++;
	}
	a = 0;
	tmp2 = ft_strdup("_=");
	tmp2 = ft_strjoin(tmp2, tmp);
	while (st->envv)
	{
		if (!ft_strcmp((char *)st->envv->content, tmp2))
			a = 1;
		else if (!ft_strncmp((char *)st->envv->content, "_=", 2))
		{
			st->envv->content = ft_strjoin("_=", tmp);                                    /////// free ft_strjoin
			a = 1;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	if (a == 0)
		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("_=", "/bin/bash")));                 ////// free ft_strjoin
	st->envv = st->firstenv;
	return (1);
}
