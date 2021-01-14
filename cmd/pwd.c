#include "../include/minishell.h"

char *ft_pwd(shell *st)
{
//	char *buf;
//	int i;
//	char *tmp;

//	i = 0;
//	tmp = NULL;
//	buf = NULL;
	st->pwd = getcwd(NULL, 0);
/*
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(tmp, "PWD=", 4))
		{
			if (st->pwd)
			{
				i = 0;
				while (tmp[i] != '=')
					i++;
				if (tmp[i] == '=')
					i++;
			//	if (!ft_strcmp(st->pwd, st->oldpwd))
				st->envv->content = ft_strjoin("PWD=", st->pwd);
//				printf("envv||%s||\n", (char *)st->envv->content);
				break;
			}
		}
		st->envv = st->envv->next;
	}
	st->envv = st->firstenv;
*/
	return (st->pwd);
}

int oldpwd(shell *st)
{
	char *tmp;
	int i;

	i = 0;
	tmp = NULL;
//	printf("tok||%s||\n", (char *)st->tokens->content);
//	printf("pwd||%s||\n", st->pwd);
//	printf("oldpwd||%s||\n", st->oldpwd);
	while (st->envv)
	{
		tmp = (char *)st->envv->content;
		if (!ft_strncmp(tmp, "OLDPWD=", 7))
		{
			i = 0;
			while (tmp[i] != '=')
				i++;
			if (tmp[i] == '=')
				i++;
			st->envv->content = ft_strjoin("OLDPWD=", st->oldpwd);
//			printf("envv||%s||\n", (char *)st->envv->content);
			break;
		}
		st->envv = st->envv->next;
	}
//	if (ft_strncmp((char *)st->envv->content, "OLDPWD=", 7) && !st->envv)
//	st->envv = st->firstenv;
//	if (!st->envv)
//		ft_lstadd_back(&st->envv, ft_lstnew(ft_strjoin("OLDPWD=", st->oldpwd)));
	st->envv = st->firstenv;
	return (0);
}
