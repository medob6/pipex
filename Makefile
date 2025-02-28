CC = cc
CFLAGS = -g #-fsanitize=address
# -Wall -Werror -Wextra
INCLUDES = -I .
SRC = pipex.c libft/*.c parser.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

NAME = pipex
RM = rm -f

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(INCLUDES) $(SRC) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ) 

fclean: clean
	@$(RM) $(NAME) 

re: fclean all