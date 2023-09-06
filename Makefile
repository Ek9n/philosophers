# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hstein <hstein@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/06 16:46:40 by hstein            #+#    #+#              #
#    Updated: 2023/09/07 00:43:28 by hstein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=thread
RM		= rm -rf
HEADERS = -I ./include
SRCS	= 	src/philosophers.c	\
			src/utils.c			\

all: $(NAME)

$(NAME):
	cc $(CFLAGS) $(SRCS) -o $(NAME) $(HEADERS)

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# NAME	= philosophers
# CC		= cc -Wall -Wextra -Werror
# CFLAGS	= -Wall -Wextra -Werror
# LIBFT  	= libft/libft.a
# HEADERS = -I ./include
# SRCS	=	./src/main.c	\
# 			./src/utils.c	\
# OBJS = $(SRCS:.c=.o)

# RM	= rm -rf

# all: $(NAME)

# libft:
# 	make -C libft

# %.o: %.c
# 	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

# $(NAME): $(OBJS)
# 	$(CC) $(OBJS) $(CFLAGS) $(HEADERS) -o $(NAME) $(LIBFT)

# # %.o: %.c
# # 	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

# # $(NAME): $(OBJS)
# # 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

# clean:
# 	make clean -C libft
# 	$(RM) $(OBJS)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
