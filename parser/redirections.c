#include "../include/minishell.h"

static int ft_isinstring(char *str, char c)
{
    int a;

    a = 0;
    while (str[a])
    {
        if (str[a] == c)
            return (1);
        a++;
    }
    return (0);
}

int ft_check_errorredir(shell *st)
{
    char *tokens;
    char *tokensnext;

    tokens = (char *)st->tokens->content;
    tokensnext = NULL;
    if (!ft_strncmp(tokens, "<>", 3))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        return (1);
    }
    if (!ft_strncmp(tokens, ">>>", 4))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `>'\n", 2);
        return (1);
    }
    if (!ft_strncmp(tokens, ">>>>", 4))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `>>'\n", 2);
        return (1);
    }
    if (!ft_strncmp(tokens, "<<<<", 5))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `<'\n", 2);
        return (1);
    }
    if (!ft_strncmp(tokens, "<<<<<", 6))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `<<'\n", 2);
        return (1);
    }
    if (!ft_strncmp(tokens, "<<<<<<", 6))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `<<<'\n", 2);
        return (1);
    }
    if (st->tokens->next)
    {
        tokensnext = (char *)st->tokens->next->content;
        if ((ft_isinstring("<>", tokensnext[0]) == 0) && !ft_strncmp(tokens, "<<", 3))
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `newline'\n", 2);
            return (1);
        }
        if ((ft_isinstring("<>", tokensnext[0]) == 0) && !ft_strncmp(tokens, "<<<", 4))
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `newline'\n", 2);
            return (1);
        }
        if (!ft_strncmp(tokensnext, "<>", 2))
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `<>'\n", 2);
            return (1);
        }
        if (!ft_strncmp(tokensnext, ">", 2))
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `>'\n", 2);
            return (1);
        }
        if (!ft_strncmp(tokensnext, ">>", 2))
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `>>'\n", 2);
            return (1);
        }
        if (!ft_strncmp(tokensnext, "<", 2))
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `<'\n", 2);
            return (1);
        }
        if (!ft_strncmp(tokensnext, "<<", 3))
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `<<'\n", 2);
            return (1);
        }
        if (!ft_strncmp(tokensnext, "<<<", 3))
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `<<<'\n", 2);
            return (1);
        }
    }
    if (tokensnext == NULL && !ft_strncmp(tokens, "<<", 3))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        return (1);
    }
    if (tokensnext == NULL && !ft_strncmp(tokens, "<<<", 4))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'\n", 2);
        return (1);
    }
/*    if (!st->tokens->next)
    {
        if (!ft_strncmp(tokens, "<<", 2))
        {
            ft_putendl_fd("minishell: syntax error near unexpected token `newline'\n", 2);
            return (1);
        }
    }*/
    return (0);
}

int ft_parse_redir(shell *st, int fd)
{
    int a;
	int i;
	char *tmp;
	char *tmp2;

    a = 0;
	i = 0;
    fd = 1;
	tmp = NULL;
	tmp2 = NULL;
	st->rd = 1;
    if (st->redir[a + 1])
    {
	    tmp = ft_strdup(st->redir[a + 1]);
		i = ft_strlen(tmp);
		while (tmp[i - 1] == ' ')
			i--;
	    tmp = ft_substr(tmp, 0, i);
	    st->redir[a + 1] = ft_strdup(ft_traduction(st, tmp));
    }
	tmp2 = ft_strdup(st->redir[a]);
	st->rd = 0;
    while (st->redir[a])
    {
        if (st->redir[1] == NULL)
        {
//            if (!st->cutline->next)
//            {
                ft_putendl_fd("minishell: syntax error near unexpected token `newline'\n", 2);
                st->status = 2;
                return (1);
//            }
        }
        if (!ft_strcmp(st->redir[a], ">"))
        {
            if ((fd = open(st->redir[a + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
                return (1);
        }
        if (!ft_strcmp(st->redir[a], ">>"))
        {
            if ((fd = open(st->redir[a + 1], O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0)
                return (1);
        }
        if (!ft_strcmp(st->redir[a], "<"))
        {
            if ((fd = open(st->redir[a + 1], O_RDONLY)) < 0)
            {
				if (errno == 2)
				{
                	write(2, "minishell: ", 11);
                	write(2, st->redir[a + 1], ft_strlen(st->redir[a + 1]));
                	write(2, ": No such file or directory\n", 28);
				}
				if (errno == 13)
				{
                	write(2, "minishell: ", 11);
                	write(2, st->redir[a + 1], ft_strlen(st->redir[a + 1]));
                	write(2, ": Permission denied\n", 20);
				}
                return (1);
            }
        }
        a++;
    }
    if (!ft_strcmp(tmp2, "<"))
    	st->fdout = dup2(fd, 0);
	else
    	st->fdout = dup2(fd, 1);
//    free(tmp2);
    return (0);
}

t_list  *ft_redirections2(shell *st, char *supp, char *supp2, char *supp3)
{
    t_list  *tmp;
    t_list  *previous;
    char    **redir;

    tmp = NULL;
    previous = st->tokens;
    redir = malloc(2 * sizeof(char *));
    redir[0] = ft_strdup("");
    redir[1] = NULL;
    if (st->tokens == NULL || supp == NULL)
    {
        ft_freetab(redir);
        return (st->tokens);
    }
    if (!ft_strcmp((char *)previous->content, supp) || !ft_strcmp((char *)previous->content, supp2) || !ft_strcmp((char *)previous->content, supp3))
    {
//        printf("previous content : |%s|\n", (char *)previous->content);
//        printf("OK\n");
        if (previous->next)
            st->redirnext = previous->next->content;
        st->tokens = previous->next;
//        printf("previous content 2: |%s|\n", (char *)previous->content);
        redir[0] = ft_strdup((char *)previous->content);
        redir[1] = NULL;
        st->redir = ft_tabjoin(st->redir, redir);
        free(previous);
        st->firsttok = st->tokens;
//        ft_freetab(redir);
        return (st->tokens);
    }
    tmp = previous->next;
    while (tmp != NULL)
    {
        if (!ft_strcmp((char *)tmp->content, supp) || !ft_strcmp((char *)tmp->content, supp2) || !ft_strcmp((char *)tmp->content, supp3))
        {
//            printf("OK2\n");
            if (tmp->next)
                st->redirnext = tmp->next->content;
            redir[0] = ft_strdup((char *)previous->next->content);
            redir[1] = NULL;
            st->redir = ft_tabjoin(st->redir, redir);
            previous->next = tmp->next;
            free(tmp);
//            ft_freetab(redir);
            return (st->tokens);
        }
        previous = tmp;
        tmp = tmp->next;
    }
    ft_freetab(redir);
    return (0);
//  printf("tok content : |%s|\n", (char *)st->tokens->content);
//  printf("firsttok content : |%s|\n", (char *)st->firsttok->content);
}

int ft_check_redir(shell *st)
{
    st->redirnext = NULL;
	st->firsttok = st->tokens;
    while (st->tokens)
    {
        st->tokens = ft_redirections2(st, ">", ">>", "<");
//        if (ft_check_errorredir2(st) == 1)
//            return (1);
        st->tokens = ft_redirections2(st, st->redirnext, st->redirnext, st->redirnext);
        st->redirnext = NULL;
    }
    st->tokens = st->firsttok;
    return (0);
}

int ft_redirections(shell *st)
{
	int fd;
    char *tokens;

	fd = 0;
    st->errorredir = 0;
    tokens = NULL;
    if (!(st->redir = malloc(1 * sizeof(char *))))
        return (1);
    st->redir[0] = NULL;
    st->firsttok = st->tokens;
    while (st->tokens)
    {
        tokens = (char *)st->tokens->content;
        if (ft_isinstring("<>", tokens[0]) == 1)
        {
            if (ft_check_errorredir(st) == 1)
                return (1);
        }
        st->tokens = st->tokens->next;
    }
    st->tokens = st->firsttok;
    if (ft_check_redir(st) == 1)
        return (1);
    if (st->redir[0] != NULL)
    {
		if (ft_parse_redir(st, fd) == 1)
  	         return (1);	
	}
    ft_freetab(st->redir);
    return (0);
}
