# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/14 09:50:50 by user42            #+#    #+#              #
#    Updated: 2021/09/14 17:43:37 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := server

NAME_C := client

SRCS_C :=	c_main.c \
			c_utils.c

SRCS_S :=	s_main.c \
			s_utils.c \
			s_list.c

OBJS_C = $(SRCS_C:c_%.c=c_%.o)

OBJS_S = $(SRCS_S:s_%.c=s_%.o)

CFLAGS += -Wall -Werror -Wextra

CC := gcc

all: $(NAME) $(NAME_C)

$(NAME): $(OBJS_S)
	$(CC) $(CFLAGS) $(OBJS_S) -o $(NAME)

$(NAME_C): $(OBJS_C)
	$(CC) $(CFLAGS) $(OBJS_C) -o $(NAME_C)

s_%.o: s_%.c server.h
	$(CC) $(CFLAGS) -c $< -o $@

c_%.o: c_%.c client.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_S) $(OBJS_C)

fclean: clean
	rm -f $(NAME) $(NAME_C)

re: fclean all

norm:
	-norminette $(SRCS_C) $(SRCS_S) server.h client.h

.PHONY: all clean fclean re norm

