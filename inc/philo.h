
#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>

# define ERR_ARGS "Wrong arguments quantity, this program require:\n1-Number of philosophrers\n2-Time to die\n3-Time to sleep\n4-Number of times each philosopher must eat\n"

/*philo.c*/
int main(int ac, char **av);

/*utils.c*/
int ft_msn(char *s, int fd);

#endif