# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hstein <hstein@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 16:46:40 by hstein            #+#    #+#              #
#    Updated: 2023/08/06 16:55:54 by hstein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
# PRINTF		= ./printf/libftprintf.a

SRCS = ./src/philo.c
OBJS = $(SRCS:.c=.o)

RM			= rm -rf

all: $(NAME)

# $(PRINTF):
# 	$(MAKE) -C ./printf
# $(NAME): $(OBJS) $(LIBFT) $(PRINTF)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(PRINTF) -o server
$(NAME): $(OBJS) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) $(PRINTF) -o $(NAME)

clean:
	$(MAKE)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
