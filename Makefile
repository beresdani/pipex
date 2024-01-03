CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LIBFT =-Llibft/ -lft
NAME = pipex
NAME2 = pipex_bonus
SRC = pipex.c list_utils.c command_errors.c pipex_utils.c

SRC2 = pipex_bonus.c multi_pipes.c list_utils.c multi_pipes_utils.c child_processes.c \
		command_errors_bonus.c
# MLX=-lXext -lX11 -lz -lm -lmlx
OBJ = $(SRC:.c=.o)
OBJ2 = $(SRC2:.c=.o)

all: $(NAME)
all2: $(NAME2)

$(NAME): $(OBJ) libft/libft.a
	cc $(OBJ) -o $(NAME) libft/libft.a

$(NAME2): $(OBJ2) libft/libft.a
	cc $(OBJ2) -o $(NAME2) libft/libft.a
	
# create o files
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

#run Makefile in libft folder
libft/libft.a:
	$(MAKE) -C libft all

clean:
	rm -rf $(OBJ) $(OBJ2)
	$(MAKE) -C libft clean

fclean: clean
	rm -rf $(NAME) $(NAME2)
	$(MAKE) -C libft fclean

re: fclean all
	$(MAKE) -C libft re

.PHONY: clean fclean cleanup re all bonus

bonus: $(NAME2)

