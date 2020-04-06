# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aglorios <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/10 12:05:15 by aglorios          #+#    #+#              #
#    Updated: 2019/11/27 16:42:24 by aglorios         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = *.c

NAME = libft.a

OBJS = $(SRC:%.c=%.o)

CFLAGS = -Wall -Wextra -Werror -I$(HEADER)

GCC = gcc

RM = rm -rf

HEADER = ./

all: $(NAME)

$(OBJS): $(SRC)
	$(GCC) $(CFLAGS) -c $(SRC)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	$(RM) $(OBJS) $(BOBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus:
	$(GCC) $(CFLAGS) -I$(HEADER) -c $(SBONUS) $(SRC)
	ar rc $(NAME) $(BOBJS)
	ranlib $(NAME)

.PHONY: all test clean fclean re
