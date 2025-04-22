NAME = minishell

CC = cc


#test to be removed
# Test build (separate target)
TEST_NAME = minishell_test
TEST_SRC = \
		./srcs/test_main.c \
		./srcs/04_execution/execution_01.c \
TEST_OBJ = $(TEST_SRC:.c=.o)



CFLAGS = -Wall -Werror -Wextra -g -Iincludes

LDFLAGS = -lreadline

# Sanitizer flags
FSANITIZER_ADDRESS_FLAG = -fsanitize=address -O2
FSANITIZER_THREAD_FLAG = -fsanitize=thread -O2

SRC = \
		./srcs/main.c \
		./srcs/01_input_validation/checks.c\
		./srcs/02_tokenization/list_token.c \
		./srcs/02_tokenization/print_token.c \
		./srcs/02_tokenization/tokenization.c \
		./srcs/02_tokenization/word_tokens.c \
		./srcs/04_execution/execution_01.c \
		./srcs/04_execution/handle_command.c \
		./srcs/05_builtin/builtin01.c \
		./srcs/05_builtin/builtin02.c \
		./srcs/06_signals/signals.c \
		./srcs/07_env_var_expansion/environment01.c \




OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libraries/ft_libft

LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean :
	rm -f $(OBJ) $(TEST_OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
#$(MAKE) -C $(LIBFT_DIR) clean
#test to be removed
	rm -f $(TEST_NAME)
	$(MAKE) -C $(LIBFT_DIR) clean

re : fclean all

# Aliases
asan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_ADDRESS_FLAG)" all
tsan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_THREAD_FLAG)" all

#test to be removed
test:
	$(MAKE) fclean
	$(MAKE) $(TEST_NAME)


$(TEST_NAME): $(TEST_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(FSANITIZER_ADDRESS_FLAG) -o $(TEST_NAME) $(TEST_OBJ) $(LIBFT) $(LDFLAGS)


.PHONY : all clean fclean re
