CC = cc
CFLAGS = -g #-fsanitize=address
# -Wall -Werror -Wextra
INCLUDES = -I .
SRC = pipex.c utils_lib/*.c parser.c 
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