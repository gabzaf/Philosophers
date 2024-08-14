NAME	:= philo
CC	:= cc
CFLAGS	:= -Wall -Wextra -Werror
RM	:= rm -rf
SRC	:= main.c parser.c exit.c utils.c init.c routine.c monitor.c	
OBJ	:= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re