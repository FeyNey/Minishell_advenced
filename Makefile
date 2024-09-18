# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexis <alexis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:05:19 by aglampor          #+#    #+#              #
#    Updated: 2024/09/18 12:23:52 by alexis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

NAME	= minishell

LDFLAGS = -lreadline #-lft

SRC_DIR = src/

SRC_FILES =		env.c\
			minishell.c\
			exe.c\
			exit.c\
			signals.c\
			builtin/f_export_no_arg.c\
			builtin/f_export_args.c\
			builtin/f_buildin.c\
			build_tokens/tok_utils.c\
			build_tokens/clean_quote.c\
			build_tokens/clean_redir.c\
			build_tokens/redir_realoc.c\
			build_tokens/tokens.c\
			utils/split_CMD.c\
			utils/env_utils.c\
			utils/utils.c\
			utils/ft_split.c\
			utils/split_ws.c\
			utils/verif.c\
			build_tokens/clear_quote2.c\
			utils/triple_join.c


SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(SRC_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
