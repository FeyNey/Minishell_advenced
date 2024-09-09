# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexis <alexis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:05:19 by aglampor          #+#    #+#              #
#    Updated: 2024/09/09 23:48:51 by alexis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

NAME	= minishell

LDFLAGS = -lreadline #-lft

SRC_DIR = src/

SRC_FILES = build_ft.c\
			env.c\
			exit.c\
			f_buildin.c\
			verif.c\
			export.c\
			exe.c\
			tok_utils.c\
			split_ws.c\
			ft_split.c\
			split_CMD.c\
			minishell.c\
			token.c\
			utils.c\
			triple_join.c\
			clear_quote2.c\
			signals.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
