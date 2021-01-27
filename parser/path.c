#include "../include/minishell.h"

static void    ft_freetab(char **tab)
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
			if (st->pat)
				free(st->pat);
			path = ft_strdup(&tmp[i]);
			st->pat = ft_strdup(&tmp[i]);
			break;
		}
		st->envv = st->envv->next;
	}
	free(cmppath);
	st->envv = st->firstenv;
	tab = ft_split(path, ':');      												///// here!!!
	free(path);
	return (tab);
}

int	check_path(shell *st, char *dollars)
{
	char *cmd;
	char *cmppath;
	char *tmp;
	char *fri;
	int i;
	int fd;
	struct stat b;
	char **tab;

	tmp = NULL;
	tab = NULL;
	cmppath = NULL;
	fri = NULL;
	i = 0;
	(void)dollars;
	cmd = (char *)st->tokens->content;
	tab = recuppath(st, tab);
	st->cmdexec = ft_strdup((char *)st->tokens->content);
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
					st->cmdexec = ft_strjoin(tmp, cmppath);
				else
					st->cmdexec = tmp;
				ft_freetab(tab);
				return (1);
			}
		}
		i++;
	}
	ft_freetab(tab);
	(void)fd;
//	fd = open(st->cmdexec, O_RDONLY, S_IRUSR | S_IWUSR);
//	i = 0;
//	if (i = stat(st->cmdexec, &b) != -1)
//	{
  //      write(1, "minishell: ", 11);
   	//    write(1, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
//       	write(1, ": No such file or directory\n", 28);
//		st->status = 126;
//		return (0);
//	}
//	close(fd);
	if (stat(st->cmdexec, &b) == -1)
	{
//		printf("ok2\n");
		return (0);
	}
	return (1);
}
