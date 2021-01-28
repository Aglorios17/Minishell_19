#include "../include/minishell.h"

void    ft_freetab(char **tab)
{
    int a;

    a = 0;
    while (tab[a])
    {
        free(tab[a]);
        tab[a] = NULL;
        a++;
    }
    free(tab);
    tab = NULL;
}

char **recuppath(shell *st, char **tab)
{
	int		i;
	char	*tmp;
	char	*path;
	char	*cmppath;

	i = 0;
	tmp = NULL;
	path = NULL;
	cmppath = ft_strdup("PATH=");
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(cmppath, tmp, ft_strlen(cmppath)))
		{
			i = 0;
			while (tmp[i] != '=')
				i++;
			if (tmp[i] == '=')
				i++;
			path = ft_strdup(&tmp[i]);
			st->pat = ft_strdup(&tmp[i]);
			break;
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
	tab = ft_split(path, ':');
	free(path);
	free(cmppath);
	return (tab);
}

int	check_path(shell *st, char *dollars)
{
	char 	*cmd;
	char 	*cmppath;
	char	*tmp;
	int		i;
	struct	stat b;
	char	**tab;
	char	*fri;

	tmp = NULL;
	tab = NULL;
	cmppath = NULL;
	fri = NULL;
	i = 0;
	(void)dollars;
	cmd = (char *)st->tokens->content;
	tab = recuppath(st, tab);
	st->cmdexec = ft_strdup((char *)st->tokens->content);                              //// free st->cmdexec si pas déjà fait
	if (tab == NULL)
		return (0);
	while (tab[i])
	{
		if (!ft_strchr(cmd, '/'))
		{
			if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") ||
				!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export") ||
				!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
			{
				ft_freetab(tab);
				return (0);
			}
			tmp = ft_strjoin(tab[i], "/");
			fri = tmp;
			tmp = ft_strjoin(tmp, cmd);
			free(fri);
			if (stat(tmp, &b) != -1)
			{
				if (cmppath)
					st->cmdexec = ft_strjoin(tmp, cmppath);                             //// free st->cmdexec si pas déjà fait
				else
					st->cmdexec = ft_strdup(tmp);                                       //// free st->cmdexec si pas déjà fait
				free(tmp);
				return (1);
			}
		}
		i++;
	}
	if (tmp)
		free(tmp);
	ft_freetab(tab);
	if (stat(st->cmdexec, &b) == -1)
		return (0);
	return (1);
}
