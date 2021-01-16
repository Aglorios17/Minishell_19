#include "../include/minishell.h"
/*
int ft_parse_redir(shell *st)
{
    int a;
    int file_desc;
    int copy_desc;
    char    *str;

    a = 0;
    copy_desc = 0;
    str = ft_strdup("");
    (void)st;
    (void)copy_desc;
    if ((file_desc = open("test.txt", O_WRONLY | O_APPEND | O_CREAT, 0644)) < 0)
        return (0);
//    copy_desc = dup(file_desc);
    write(file_desc, "XD\n", 3);

    return (0);
}
*/
int ft_redirections2(shell *st)
{
    t_list  *tmp;
    t_list  *previous;
    char    *tokens;

    tmp = NULL;
    (void)tmp;
    previous = st->tokens;
    tokens = (char *)st->tokens->content;
    (void)tokens;
    if ((st->tokens == st->firsttok))
    {
//        printf("tok content : |%s|\n", (char *)st->tokens->content);
        st->tokens = previous->next;
        free(previous);
        st->firsttok = st->tokens;
        return (0);
    }
    tmp = previous->next;
    while (tmp)
	{
//        printf("tok content : |%s|\n", (char *)st->tokens->content);
//        printf("tmp content : |%s|\n", (char *)tmp->content);
		if (!ft_strcmp(tokens, (char *)previous->content))
		{
			previous->next = tmp->next;
			free(tmp);
	//		st->tokens = st->firsttok;
			return (0);
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
    while (st->tokens)
    {
        if (st->tokens->next && (!ft_strcmp((char *)st->tokens->next->content, ">") || !ft_strcmp((char *)st->tokens->next->content, ">>") || !ft_strcmp((char *)st->tokens->next->content, "<")))
        {
            while (st->tokens->next)
            {
                if (ft_strcmp((char *)st->tokens->next->content, ">") && ft_strcmp((char *)st->tokens->next->content, ">>") && ft_strcmp((char *)st->tokens->next->content, "<"))
                    break ;
                ft_redirections2(st);
                ft_redirections2(st);
            }
        }
        if (st->tokens == st->firsttok && (!ft_strcmp((char *)st->tokens->content, ">") || !ft_strcmp((char *)st->tokens->content, ">>") || !ft_strcmp((char *)st->tokens->content, "<")))
        {
            ft_redirections2(st);
            ft_redirections2(st);
        }
        else
            st->tokens = st->tokens->next;
    }
    st->tokens = st->firsttok;
    return (0);
}

int ft_redirections(shell *st)
{
    ft_check_redir(st);
//    if (st->redir[0])
//        ft_parse_redir(st);
//    printf("redir : |%s|\n", st->redir);
//    free(st->redir);
    return (0);
}