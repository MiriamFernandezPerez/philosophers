CC = gcc

NAME = philo

HEADER_NAME = philo.h

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address -fsanitize=leak 

SRC = src/philo.c \
      src/utils.c \
      src/check_arg.c \
      src/init.c \
      src/handle_thread.c \
      src/handle_mutex.c \
      src/start.c \
      src/routine.c \
      src/end_simulation.c \
      src/monitor.c \
      

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Makefile
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c $(HEADER_NAME)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
