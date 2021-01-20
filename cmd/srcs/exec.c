#include "../../include/minishell.h"

int ft_error(shell *st, struct stat b)
{
	int		fd;
	char	*cmd;
	DIR		*dir;

	fd = 0;
//	cmd = ft_strdup((char *)st->tokens->content);
	cmd = st->cmdexec;
//	fd = open(cmd, O_RDONLY, S_IRUSR | S_IWUSR);
	(void)fd;
	(void)b;
	(void)dir;
//	printf("fd|%i|\n", fd);
//	printf("cmdexec|%s|\n", cmd);
//	printf("st->tokens|%s|\n", (char *)st->tokens->content);
//	dir = opendir(cmd);
//	if (dir != NULL)
//	{
//		fd = open(st->cmdexec, O_RDONLY, S_IRUSR | S_IWUSR | S_IXUSR);
//		stat(cmd, &b);
//	}
	if (stat(cmd, &b) == -1)
	{
		write(1, "minishell: ", 11);
     	write(1, (char *)st->tokens->content, ft_strlen((char *)st->tokens->content));
 		write(1, ": command not found\n", 20);
		st->status = 127;
		return (0);
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
//	int fd;

	ar = NULL;
	en = NULL;
	i = 0;
	(void)b;
//	fd = 0;
//	printf("tokens|%s|\n", (char *)st->tokens->content);	
//	printf("st->cmd|%s|\n", st->cmdexec);
	if (ft_error(st, b) == 0)
		return (0);
///////////////////////////////////////////////////////// error ///////////////
/*
	if ((fd = open(st->cmdexec, i)))
	{
		printf("errno|%i|\n", errno);	
		printf("fd1|%i|\n", fd);	
		if (errno == 13)
		{
			write(1, "minishell: ", 11);
			write(1, st->cmdexec, ft_strlen(st->cmdexec));
			write(1, ": Permission denied\n", 20);
			st->status = 126;
			return (0);
		}
	}
	printf("fd2|%i|\n", fd);	
	close(fd);
*/
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
