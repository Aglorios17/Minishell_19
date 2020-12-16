#include "minishell.h"

int	check_path(shell *st)
{
	char *cmd;
	char *path;
	char *cmppath;
	char *tmp;
	int i;
	struct stat b;
	char **tab;

	tmp = NULL;
	tab = NULL;
	path = NULL;
	cmd = (char *)st->tokens->content;
	cmppath = ft_strdup("PATH=");
	i = 0;
	while (st->envv)
	{
		tmp = ft_strdup((char *)st->envv->content);
		if (!ft_strncmp(cmppath, tmp, ft_strlen(cmppath)))
		{
			i = 0;
			while (tmp[i] != '=')
				i++;
			if (tmp[i] == '=')
				i++;
			path = ft_strdup(&tmp[i]);
			break;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	//////////////////////////////////// fin recup path
	tab = ft_split(path, ':');
	if (!tab)
		(void)tab;
	if (stat(cmd, &b) == -1)
		return (0);
	return (1);
}

static char **ft_tabreturn(t_list *list)
{
	t_list *tmp;
	char **tab;
	int i;
	
	tab = NULL;
	i = 0;
	tmp = list;
	if ((tab = malloc(sizeof(char *) * ft_lstsize(list) + 1)) == NULL)
		return (0);
	while (list)
	{
		tab[i] = ft_strdup((char *)list->content);
		i++;
		list = list->next;
	}
	tab[i] = NULL;
	list = tmp;
	return (tab);
}

int ft_exec(shell *st)
{
	char **ar;
	char **en;
	int i;
	int a;

	ar = NULL;
	en = NULL;
	a = fork();
	ar = ft_tabreturn(st->tokens);
	en = ft_tabreturn(st->envv);
	if (a == 0)
		i = execve((char *)st->tokens->content, ar, en);
	wait(&a);
	return (i);
}
