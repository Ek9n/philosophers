# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hstein <hstein@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 16:46:40 by hstein            #+#    #+#              #
#    Updated: 2023/08/23 14:18:20 by hstein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosophers
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LIBFT  	= libft/libft.a
SRCS	=	./src/philo.c	\
			./src/utils.c	\
OBJS = $(SRCS:.c=.o)

RM			= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
