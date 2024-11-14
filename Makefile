CC = gcc

NAME = philo

HEADER_NAME = inc/philo.h

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=leak

HEADER_DIR = inc/

INCLUDES = -I $(HEADER_DIR)

SRC = src/philo.c\
      src/utils.c\
	  src/check_arg.c\
	  src/handle_thread.c\
	  src/handle_mutex.c\
	  src/init.c\
	  src/start.c\
			src/monitor.c\

OBJS = $(SRC:.c=.o)

DEPS = $(SRC:.c=.d)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER_NAME)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Regla para compilar .o y generar .d automáticamente
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

# Incluir los archivos .d con las dependencias
-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
