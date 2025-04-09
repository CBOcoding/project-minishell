NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -Iincludes
LDFLAGS = -lreadline

# Sanitizer flags
FSANITIZER_ADDRESS_FLAG = -fsanitize=address -O2
FSANITIZER_THREAD_FLAG = -fsanitize=thread -O2

SRC = \
		./srcs/main.c \
		./srcs/06_signals/signals.c \
		./libraries/ft_getnextline/get_next_line_bonus.c \
		./libraries/ft_getnextline/get_next_line_utils_bonus.c \


OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libraries/ft_libft

LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean :
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean : clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) clean

re : fclean all

# Aliases
asan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_ADDRESS_FLAG)" all
tsan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_THREAD_FLAG)" all

.PHONY : all clean fclean re