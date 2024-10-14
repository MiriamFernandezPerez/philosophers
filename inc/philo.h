
#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>

# define ERR_ARGS "Wrong arguments quantity, typeee\n"

/*philo.c*/
int main(int ac, char **av);

/*utils.c*/
int ft_msn(char *s, int fd);

#endif