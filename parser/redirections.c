#include "../include/minishell.h"

int ft_check_errorredir2(shell *st)
{
    if (st->redirnext && !ft_strncmp(st->redirnext, ">", 2))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `>'\n", 2);
        return (1);
    }
    if (st->redirnext && !ft_strncmp(st->redirnext, ">>", 2))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `>>'\n", 2);
        return (1);
    }
    if (st->redirnext && !ft_strncmp(st->redirnext, "<", 1))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `<'\n", 2);
        return (1);
    }
    if (st->redirnext && !ft_strncmp(st->redirnext, "<<", 2))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `<<'\n", 2);
        return (1);
    }
    return (0);
}

int ft_check_errorredir(shell *st)
{
    if (!ft_strncmp((char *)st->tokens->content, ">>>", 4))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `>'\n", 2);
        return (1);
    }
    if (!ft_strncmp((char *)st->tokens->content, ">>>>", 4))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `>>'\n", 2);
        return (1);
    }
    if (!ft_strncmp((char *)st->tokens->content, "<<<<", 5))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `<'\n", 2);
        return (1);
    }
    if (!ft_strncmp((char *)st->tokens->content, "<<<<<", 6))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `<<'\n", 2);
        return (1);
    }
    if (!ft_strncmp((char *)st->tokens->content, "<<<<<<", 6))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `<<<'\n", 2);
        return (1);
    }
    return (0);
}

int ft_parse_redir(shell *st, int fd)
{
    int a;

    a = 0;
    fd = 1;
    while (st->redir[a])
    {
        if (st->redir[1] == NULL)
        {
            if (st->cutline->next)
                ft_putendl_fd("minishell: syntax error near unexpected token `;\'\n", 2);
            else
                ft_putendl_fd("minishell: syntax error near unexpected token `newline'\n", 2);
            return (1);
        }
        if (!ft_strcmp(st->redir[a], ">"))
        {
            if ((fd = open(st->redir[a + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
                return (0);
        }
        if (!ft_strcmp(st->redir[a], ">>"))
        {
            if ((fd = open(st->redir[a + 1], O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0)
                return (0);
        }
        if (!ft_strcmp(st->redir[a], "<"))
            if ((fd = open(st->redir[a + 1], O_RDONLY)) < 0)
                return (0);
        a++;
    }
//	printf("ok\n");
//	st->fdone = st->fdout;
//	printf("fdone|%i|\n", st->fdone);
//	close(1);
 //   st->fdout = dup2(fd, 1);
    st->fdout = dup2(fd, 1);
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
        return (st->tokens);
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
            return (st->tokens);
        }
        previous = tmp;
        tmp = tmp->next;
    }
    return (0);
//  printf("tok content : |%s|\n", (char *)st->tokens->content);
//  printf("firsttok content : |%s|\n", (char *)st->firsttok->content);
}

int ft_check_redir(shell *st)
{
    st->redirnext = NULL;
/*    while (st->tokens)
    {
        if (ft_check_errorredir(st) == 1)
            return (1);
        st->tokens = st->tokens->next;
    }
    st->tokens = st->firsttok;
*/
	st->firsttok = st->tokens;
    while (st->tokens)
    {
        st->tokens = ft_redirections2(st, ">", ">>", "<");
        if (ft_check_errorredir2(st) == 1)
            return (1);
        st->tokens = ft_redirections2(st, st->redirnext, st->redirnext, st->redirnext);
        st->redirnext = NULL;
    }
    st->tokens = st->firsttok;
    return (0);
}

int ft_redirections(shell *st)
{
	int fd;

	fd = 0;
    if (!(st->redir = malloc(1 * sizeof(char *))))
        return (1);
    st->redir[0] = NULL;
    st->firsttok = st->tokens;
    while (st->tokens)
    {
        if (ft_check_errorredir(st) == 1)
            return (1);
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
    return (0);
}
