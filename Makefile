NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

# Sanitizer flags
FSANITIZER_ADDRESS_FLAG = -fsanitize=address -O2
FSANITIZER_THREAD_FLAG = -fsanitize=thread -O2

SRC = \
		main.c \

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

# Aliases
asan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_ADDRESS_FLAG)" all
tsan:
	$(MAKE) fclean
	$(MAKE) CFLAGS="$(CFLAGS) $(FSANITIZER_THREAD_FLAG)" all

.PHONY : all clean fclean re