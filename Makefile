NAME        = push_swap
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
SRC         = main.c parser.c parser_utils.c parser_utils2.c \
              ft_split.c ft_strncmp.c p_functions.c s_functions.c \
              r_functions.c rr_functions.c ra_rra_handlers.c \
              n_square.c n_square_utils.c utils.c print_stack.c radix.c k_sort.c
OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
