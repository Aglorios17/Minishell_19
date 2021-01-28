#include "../../include/minishell.h"

int open_pathcd(shell *st, char *path)
{
	if (errno == 13)
	{
		if (!ft_strcmp((char *)st->tokens->content, "cd\0"))
		{
			write(1, "minishell: ", 11);
			write(1, "cd: ", 4);
			write(1, path, ft_strlen(path));
			write(1, ": Permission denied\n", 20);
		}
		else
		{
			write(1, "minishell: ", 11);
			write(1, path, ft_strlen(path));
			write(1, ": Permission denied\n", 20);
		}
		return (0);
	}
	if (errno == 2)
	{
		if (!ft_strcmp((char *)st->tokens->content, "cd\0"))
		{
			write(1, "minishell: ", 11);
			write(1, "cd: ", 4);
			write(1, path, ft_strlen(path));
			write(1, ": No such file or directory\n", 28);
		}
		return (0);
	}
	return (1);
}

int ft_cd(shell *st)
{
	int i;
	char *line;
	char *tmp;
	char *env;

	i = 0;
	tmp = st->oldpwd;
	st->oldpwd = st->pwd;
	line = NULL;
	if (st->tokens->next && st->tokens->next->next)
	{
		st->oldpwd = tmp;
		write(1, "minishell: ", 11);
		write(1, "cd: ", 4);
		write(1, "too many arguments\n", 19);
		return (0);
	}
	if (!st->tokens->next)
	{	
		while (st->envv)
		{
			env = (char *)st->envv->content;
			if (!ft_strncmp(env, "HOME=", 5))
			{
				i = 0;
				while (env[i] != '=')
					i++;
				if (env[i] == '=')
					i++;
				line = ft_strdup(&env[i]);
				break;
			}
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
		st->pwd = ft_strdup(line);
		if (chdir(st->pwd) < 0)
		{
			st->oldpwd = tmp;
			write(1, "minishell: ", 11);
			write(1, "cd: ", 4);
			write(1, "HOME not set\n", 13);
			if (line)
				free(line);
			return (0);
		}
		oldpwd(st);
		if (line)
			free(line);
		return (1);
	}
	if (line)
		free(line);
	line = ft_strdup((char *)st->tokens->next->content);
	if (st->tokens->next && line[0] != '\0')
		st->pwd = ft_strdup(&line[i]);
	if (!ft_strncmp(st->pwd, "~\0", 2))
	{
		while (st->envv)
		{
			env = (char *)st->envv->content;
			if (!ft_strncmp(env, "HOME=", 5))
			{
				i = 0;
				while (env[i] != '=')
					i++;
				if (env[i] == '=')
					i++;
				st->pwd = ft_strdup(&env[i]);
				break;
			}
			st->envv = st->envv->next;
		}
		st->envv = st->firstenv;
	}
	if (chdir(st->pwd) < 0)
	{
		open_pathcd(st, (char *)st->tokens->next->content);
		st->oldpwd = tmp;
		if (line)
			free(line);
		return (0);
	}
	if (line)
		free(line);
	oldpwd(st);
	return (1);
}
