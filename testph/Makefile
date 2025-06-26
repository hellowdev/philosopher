CC = cc
# -fsanitize=thread -g
CFLAGS = -Wall -Wextra -Werror 

NAME = philo

SRC = 	philo.c \
		tools/ft_atoi.c \
		tools/ft_isdigit.c\
		little_parce.c\
		inite_mutexes.c\
		inite_functions.c\
		tasks.c\
		monitor.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -pthread

%.o : %.c philo.h
	@$(CC) $(CFLAGS)  -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

ac: all clean