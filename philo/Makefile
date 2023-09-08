# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hstein <hstein@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 16:46:40 by hstein            #+#    #+#              #
#    Updated: 2023/09/08 22:28:25 by hstein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=thread
RM		= rm -rf
HEADERS = -I ./include
SRCS	= 	src/philosophers.c	\
			src/utils_1.c		\
			src/utils_2.c		\
			src/utils_3.c		\
			src/utils_4.c		\

all: $(NAME)

$(NAME):
	cc $(CFLAGS) $(SRCS) -o $(NAME) $(HEADERS)

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
