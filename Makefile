# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cborrome <cborrome@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 17:42:52 by cborrome          #+#    #+#              #
#    Updated: 2025/05/15 17:42:52 by cborrome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -Iincludes
LDFLAGS = -lreadline

# Sanitizer flags
FSANITIZER_ADDRESS_FLAG = -fsanitize=address -O2
FSANITIZER_THREAD_FLAG  = -fsanitize=thread -O2

SRC = \
	./srcs/main.c \
	./srcs/01_input_validation/checks.c \
	./srcs/02_tokenization/list_token.c \
	./srcs/02_tokenization/tokenization_01.c \
	./srcs/02_tokenization/tokenization_02.c \
	./srcs/02_tokenization/tokenization_03.c \
	./srcs/02_tokenization/word_tokens.c \
	./srcs/02_tokenization/quote_token_01.c \
	./srcs/02_tokenization/quote_token_02.c \
	./srcs/03_parsing/parse.c \
	./srcs/03_parsing/parse_helper.c \
	./srcs/03_parsing/parse_redirection.c \
	./srcs/04_execution/execution_01.c \
	./srcs/04_execution/execution_02.c \
	./srcs/04_execution/execution_03.c \
	./srcs/04_execution/handle_command.c \
	./srcs/04_execution/heredoc.c \
	./srcs/05_builtin/builtin.c \
	./srcs/05_builtin/cd.c \
	./srcs/05_builtin/echo.c \
	./srcs/05_builtin/env.c \
	./srcs/05_builtin/export01.c \
	./srcs/05_builtin/export02.c \
	./srcs/05_builtin/export03.c \
	./srcs/05_builtin/pwd.c \
	./srcs/05_builtin/unset.c \
	./srcs/05_builtin/exit.c \
	./srcs/06_signals/signals.c \
	./srcs/07_env_var_expansion/environment.c \
	./srcs/utils/utils.c \
	./srcs/utils/utils_2.c \
	./srcs/utils/utils_3.c \
	./srcs/utils/utils_4.c \
	./srcs/utils/utils_4.c \
	./srcs/utils/utils_main_2.c \
	./srcs/utils/utils_main_1.c \
	./srcs/utils/ft_split.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Sanitizer builds
asan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_ADDRESS_FLAG)" all

tsan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_THREAD_FLAG)" all

.PHONY: all clean fclean re asan tsan