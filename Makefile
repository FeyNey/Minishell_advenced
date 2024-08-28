# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:05:19 by aglampor          #+#    #+#              #
#    Updated: 2024/08/27 15:34:29 by acoste           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

NAME	= minishell

LDFLAGS = -lreadline #-lft

SRC_DIR = src/

SRC_FILES =	structure/env.c\
			structure/build_ft.c\
			structure/exit.c\
			structure/ft_split.c\
			structure/verif.c\
			structure/split_ws.c\
			structure/minishell.c\
			structure/tokken.c\
			structure/utils.c\
			structure/triple_join.c\
			structure/signals.c\
			arthur/f_buildin.c\
			arthur/export.c\
			arthur/exe.c\
			alexis/ft_env.c
#			alexis/echo.c\

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_ARTHUR) -o $(NAME) $(LDFLAGS)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
