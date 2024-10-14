CC = gcc

NAME = philo

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak

HEADER_DIR = inc/

INCLUDES = -I $(HEADER_DIR)

SRC = src/philo.c\
	src/utils.c\

OBJS = $(SRC:.c=.o)

DEPS = $(SRC:.c=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
