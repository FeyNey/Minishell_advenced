# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:05:19 by aglampor          #+#    #+#              #
#    Updated: 2024/09/15 19:37:59 by acoste           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

NAME	= minishell

LDFLAGS = -lreadline #-lft

SRC_DIR = src/

SRC_FILES =		env.c\
			exit.c\
			builtin/f_buildin.c\
			utils/verif.c\
			builtin/f_export_no_arg.c\
			builtin/f_export_args.c\
			exe.c\
			utils/env_utils.c\
			build_tokens/tok_utils.c\
			utils/split_ws.c\
			utils/ft_split.c\
			build_tokens/cleaning.c\
			build_tokens/redir_realoc.c\
			utils/split_CMD.c\
			minishell.c\
			build_tokens/tokens.c\
			utils/utils.c\
			signals.c\
			build_tokens/clear_quote2.c\
			utils/triple_join.c


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
