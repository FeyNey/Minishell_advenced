# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alexis <alexis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 15:05:19 by aglampor          #+#    #+#              #
#    Updated: 2024/10/11 14:16:40 by alexis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

NAME	= minishell

LDFLAGS = -lreadline #-lft

SRC_DIR = src/

SRC_FILES =		env.c\
			minishell.c\
			execute.c\
			exit.c\
			signals.c\
			builtin/f_export_no_arg.c\
			builtin/f_export_args.c\
			builtin/f_buildin.c\
			build_tokens/tok_utils.c\
			build_tokens/clean_quote.c\
			build_tokens/clean_pip.c\
			build_tokens/clean_redir.c\
			build_tokens/redir_realoc.c\
			build_tokens/tokens.c\
			utils/split_CMD.c\
			utils/env_utils.c\
			utils/ft_split.c\
			utils/exe_utils.c\
			utils/utils.c\
			utils/pipe_utils.c\
			utils/split_ws.c\
			utils/verif.c\
			utils/triple_join.c\
			cd.c\
			utils/ft_itoa.c\
			builtin/pwd.c\
			build_tokens/clear_quote2.c\
			utils/ft_print.c\
			utils/ft_printf.c\
			utils/clear_utils.c\
			build_tokens/env_detection.c\
			build_tokens/env_analysis.c\
			cd_utils.c

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
