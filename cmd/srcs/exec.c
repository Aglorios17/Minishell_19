#include "../../include/minishell.h"

int	check_path(shell *st, char *dollars)
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
//	st->pat = NULL;
	cmppath = ft_strdup("PATH=");
	i = 0;
//	printf("1\n");
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
//	printf("2\n");
	//////////////////////////////////// fin recup path
//	printf("tokens|%s|\n", (char *)st->tokens->content);
//	printf("cmd |%s|\n", cmd);

//	if (!ft_strcmp(cmd, "cd\0") && st->tokens->next)
//	{
//		if (!open_path(st, (char *)st->tokens->next->content))
//			return (0);
//	}
/*	if (!ft_strncmp(cmd, "./", 2))
	{
		if (!open_path(st, (char *)st->tokens->content))
			return (0);
	}
*/	//////////////////////////////////// open path
	tab = ft_split(path, ':');
	i = 0;
	tmp = NULL;
	cmppath = NULL;
//	printf("dollars |%s|\n", dollars);
//	printf("dollars1 |%s|\n", dollars);
	if (dollars[i] && ft_strchr(dollars, ' '))
	{
		st->cmdexec = ft_strdup("");
		while (dollars[i] && dollars[i] == ' ')
			i++;
		if (!dollars[i])
			return (0);
		while (dollars[i] && dollars[i] != ' ')
		{
			st->cmdexec = ft_charjoin(st->cmdexec, dollars[i]);
			i++;
		}
		cmd = st->cmdexec;
		if (!ft_strcmp(cmd, "echo")) /////////////////////////////// check commmmande builtin
		{
//			printf("cmd |%s|\n", cmd);
			return (0);
		}
		st->tokens->content = cmd; ///////////// remplacer token
		while (dollars[i]) ////////////////////////// modif while
		{
			cmppath = ft_strdup("");
			while (dollars[i] == ' ')
				i++;
			while (dollars[i] && dollars[i] != ' ')
			{
				cmppath = ft_charjoin(cmppath, dollars[i]);
				i++;
			}
//			printf("st->tokens|%s|\n", (char *)st->tokens->content);
			ft_lstadd_back(&st->tokens, ft_lstnew(cmppath)); ///////////// remplacer token
			i++;
		}
	}
	else
		st->cmdexec = ft_strdup((char *)st->tokens->content);
//	printf("cmppath|%s|\n", cmppath);
//	printf("cmd |%s|\n", cmd);
//	write(1, "1\n", 2);
//	write(1, "2\n", 2);
	i = 0;
//	printf("tab|%s|\n", tab[i]);
	while (tab[i])
	{
//		printf("3\n");
//		printf("tab|%s|\n", tab[i]);
//		write(1, "1\n", 2);
		if (!ft_strchr(cmd, '/'))
		{
//			write(1, "2\n", 2);
//			printf("tokens|%s|\n", (char *)st->tokens->content);
//			printf("4\n");
			if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "pwd") ||
				!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export") ||
				!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "exit"))
				return (0);
//			printf("5\n");
			tmp = ft_strjoin(tab[i], "/");
			tmp = ft_strjoin(tmp, cmd);
			if (stat(tmp, &b) != -1)
			{
			//	st->tokens->content = tmp;
				if (cmppath)
					st->cmdexec = ft_strjoin(tmp, cmppath);
				else
					st->cmdexec = tmp;
				return (1);
			}
		}
		i++;
	}
	if (stat(st->cmdexec, &b) == -1)
	{
//		printf("ok\n");
		return (0);
	}
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
	struct stat b;
	int i;
	int a;
	int fd;

	ar = NULL;
	en = NULL;
	i = 0;
	fd = 0;
//	printf("tokens|%s|\n", (char *)st->tokens->content);	
//	printf("st->cmd|%s|\n", st->cmdexec);
///////////////////////////////////////////////////////// error ///////////////
///*
	if (stat(st->cmdexec, &b) == -1)
	{
		return (0);
	}
	if ((fd = open(st->cmdexec, i)))
	{
//		printf("errno|%i|\n", errno);	
//		printf("fd1|%i|\n", fd);	
		if (errno == 13)
		{
			write(1, "minishell: ", 11);
			write(1, st->cmdexec, ft_strlen(st->cmdexec));
			write(1, ": Permission denied\n", 20);
			st->status = 126;
			return (0);
		}
	}
//	printf("fd2|%i|\n", fd);	
	close(fd);
//*/
//////////////////////////////////////////////////////// fin error ///////////////////
	a = fork();
	ar = ft_tabreturn(st->tokens);
	en = ft_tabreturn(st->envv);
	if (a == 0)
		i = execve((char *)st->cmdexec, ar, en);
	wait(&a);
	st->status = a/256;
//	printf("st->status|%i|\n", st->status);
	return (i);
}
