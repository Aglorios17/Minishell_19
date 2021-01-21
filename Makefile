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
					parser/tokens.c \
					parser/quotes.c \
					parser/path.c \
					parser/ft_cutline.c \
					parser/redirections.c \
					cmd/command.c \
					cmd/srcs/export.c \
					cmd/srcs/exec.c \
					cmd/srcs/exit.c \
					cmd/srcs/env.c \
					cmd/srcs/unset.c \
					cmd/srcs/cd.c \
					cmd/srcs/echo.c \
					cmd/srcs/pwd.c \
					utils/dollars.c \
					utils/ft_splitms.c \
					utils/status.c \
					utils/lst_addin.c \
					utils/lst_cmd.c \
					utils/list_to_tab.c \

OBJS			= ${SRCS:.c=.o}
INCLUDE 		= include/minishell.h
#FOLDER			= srcs
LIBFT 			= libft
CC				= gcc -Wall -Wextra -Werror -g # -fsanitize=address
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
