# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aglorios <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/20 13:33:12 by aglorios          #+#    #+#              #
#    Updated: 2020/03/11 14:39:59 by aglorios         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell
LIBFT_PATH 		= ./libft
SRCS 			= main/main.c \
					main/free.c \
					main/signal.c \
					parser/token/tokens.c \
					parser/token/checkspace.c \
					parser/token/checkspace2.c \
					parser/token/ft_cutline.c \
					parser/token/syntax_error/ft_syntax_error.c \
					parser/token/syntax_error/ft_syntax_redir.c \
					parser/token/syntax_error/ft_syntax_semicolon_pipe.c \
					parser/cleantoken/quotes.c \
					parser/traduction/traduction.c \
					parser/traduction/traduction2.c \
					parser/traduction/ft_double_quote.c \
					parser/traduction/ft_single_quote.c \
					parser/traduction/ft_back.c \
					parser/path/path.c \
					parser/path/recup_path.c \
					parser/redirection/redirections.c \
					parser/redirection/redirections2.c \
					parser/redirection/parse_redir.c \
					parser/redirection/redirections_error.c \
					cmd/command.c \
					cmd/srcs/export/export.c \
					cmd/srcs/export/exporterror.c \
					cmd/srcs/export/exportnoparams.c \
					cmd/srcs/exec/exec.c \
					cmd/srcs/exec/exec_error.c \
					cmd/srcs/exit/exit.c \
					cmd/srcs/env/env.c \
					cmd/srcs/unset/unset.c \
					cmd/srcs/cd/cd.c \
					cmd/srcs/cd/cd_error.c \
					cmd/srcs/echo/echo.c \
					cmd/srcs/pwd/pwd.c \
					utils/dollars/cmdcommand.c \
					utils/dollars/dollars.c \
					utils/dollars/retokens.c \
					utils/dollars/dolredic.c \
					utils/dollars/retokensrd.c \
					utils/splitms/ft_splitms.c \
					utils/splitms/ft_splitms_norme.c \
					utils/lst_cmd.c \
					utils/list_to_tab.c \

OBJS			= ${SRCS:.c=.o}
INCLUDE 		= include/minishell.h
#FOLDER			= srcs
LIBFT 			= libft
CC				= gcc -Wall -Wextra -Werror -g  #-fsanitize=address
RM				= rm -f
LIBFLAGS 		= -I ./libft -L ./libft -L . ./libft/*.c 
# -I Add the directory dir to the list of directories to be searched for header files
# -L Searches the library when linking

all:			libft_all ${NAME}
$(NAME):		${OBJS} 
				@$(CC) $(LIBFLAGS) libft/libft.a -I./ $(OBJS) -o $@ 
clean:			libft_clean
				@${RM} ${OBJS}
fclean:			libft_fclean clean
				@${RM} ${NAME}
re:				fclean all

# In this last section we make other makefiles compile with the -C flag
# The -C flag makes you go to the appropriate path and do the asked command
libft_all:
	make -C $(LIBFT_PATH) all

libft_clean:
	make -C $(LIBFT_PATH) clean

libft_fclean:
	make -C $(LIBFT_PATH) fclean
	$(RM) libft/libft.a

.PHONY: all fclean clean re
