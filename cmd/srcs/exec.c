#include "../../include/minishell.h"

int ft_error(shell *st, struct stat b)
{
	char	*cmd;
	DIR		*dir;
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (st->envv)
	{
		tmp = ft_strdup((char *)st->envv->content);
		if (!ft_strncmp("PATH=", tmp, 5))
			break;
		st->envv = st->envv->next;
		tmp = NULL;
	}
	st->envv = st->envv;
	if (tmp != NULL)
	{
		while (tmp[i] && tmp[i] != '=')
			i++;
	}
	if (tmp == NULL || tmp[i + 1] == '\0')
	{
		write(2, "minishell: ", 11);
     	write(2, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
 		write(2, ": No such file or directory\n", 28);
		st->status = 127;
		return (0);
	}
	//////////////////////////////////////////////////////////////////// debug
//	printf("cmdexec|%s|\n", st->cmdexec);
//	printf("st->tokens|%s|\n", (char *)st->tokens->content);
//	printf("tmp|%s|\n", tmp);
	//////////////////////////////////////////////////////////////////// pas toucher
	if (!ft_strchr((char *)st->tokens->content, '/'))
	{
		cmd = ft_strdup(st->cmdexec);
		if (!ft_strcmp(cmd, (char *)st->tokens->content))
		{
			write(2, "minishell: ", 11);
    	 	write(2, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
 			write(2, ": command not found\n", 20);
			st->status = 127;
			return (0);
		}
	}
	cmd = ft_strdup((char *)st->tokens->content);
	dir = opendir(cmd);
	if (dir != NULL || errno == 13)
	{
		write(2, "minishell: ", 11);
     	write(2, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
		write(2, ": is a directory\n", 17);
		st->status = 126;
		closedir(dir);
		return (0);
	}
	else if (ft_strchr(cmd, '/') && stat(cmd, &b) == -1)
	{
		write(2, "minishell: ", 11);
     	write(2, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
 		write(2, ": No such file or directory\n", 28);
		st->status = 127;
		return (0);
	}
	if (stat(cmd, &b) == 0)
	{
		if (!(b.st_mode & S_IRUSR && b.st_mode & S_IXUSR))
		{
			write(2, "minishell: ", 11);
     		write(2, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
			write(2, ": Permission denied\n", 20);
			st->status = 126;
			return (0);
		}
	}
	return (1);
}

int ft_exec(shell *st)
{
	char **ar;
	char **en;
	struct stat b;
	int i;
	int a;

	ar = NULL;
	en = NULL;
	i = 0;
//	printf("tokens|%s|\n", (char *)st->tokens->content);
//	printf("st->cmd|%s|\n", st->cmdexec);
	if (ft_error(st, b) == 0)
		return (0);
	a = fork();
	ar = ft_tabreturn(st->tokens);
	en = ft_tabreturn(st->envv);
	if (a == 0)
		i = execve((char *)st->cmdexec, ar, en);
	if (errno == 13)
	{
		write(2, "minishell: ", 11);
		write(2, st->cmdexec, ft_strlen(st->cmdexec));
		write(2, ": Permission denied\n", 20);
		st->status = 126;
		return (0);
	}
//	printf("errno|%i|\n", errno);
	wait(&a);
	st->status = a/256;
//	printf("st->status|%i|\n", st->status);
//	printf("st->status|%i|\n", st->status);
	return (i);
}