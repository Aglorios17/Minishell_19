#include "../include/minishell.h"

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
		tmp = ft_strdup((char *)st->envv->content);
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
	return (tab);
}

int	check_path(shell *st, char *dollars)
{
	char *cmd;
	char *cmppath;
	char *tmp;
	int i;
	int fd;
	struct stat b;
	char **tab;

	tmp = NULL;
	tab = NULL;
	cmppath = NULL;
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
				return (0);
			tmp = ft_strjoin(tab[i], "/");
			tmp = ft_strjoin(tmp, cmd);
			if (stat(tmp, &b) != -1)
			{
				if (cmppath)
					st->cmdexec = ft_strjoin(tmp, cmppath);
				else
					st->cmdexec = tmp;
				return (1);
			}
		}
		i++;
	}
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
