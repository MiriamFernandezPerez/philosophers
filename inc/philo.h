
#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define ERR_ARGS "Wrong arguments quantity, this program require:\n1-Number of philosophers\n2-Time to die\n3-Time to eat\n4-Time to sleep\n5-Number of times each philosopher must eat (Optional)\n"
# define NEG "Negative values are not allowed\n"
# define MAX "Number too big, can't be higher than MAX_INT\n"
# define NOT_DIG "Error. Not a digit value\n"
# define ZERO "Number Zero not allowed\n"
# define NO_TIME "Use more than 60ms\n"

typedef struct s_data t_data;

typedef struct s_fork
{
    int                 fork_id;
    pthread_mutex_t     fork;
}   t_fork;

typedef struct s_philo
{
    int         id;
    long        num_meals;
    int         flag_full;
    long        last_meal;
    t_fork      *left;
    t_fork      *right;
    pthread_t   thread_id;   
}   t_philo;

struct s_data
{
    long    num_philo;
    long    time_die;
    long    time_eat;
    long    time_sleep;
    long    max_meals;
    long    start;
    long    end;
    t_fork  *forks;
    t_philo *philos;
};

/*philo.c*/
int main(int ac, char **av);

/*utils.c*/
int	check_limits(long int n);
int	ft_isdigit(char c);
int	ft_isspace(char c);
int	ft_strlen(char *s);
int ft_msn(char *s, int fd);

/*check_arg*/
void check_arg(t_data *data, char **av, int ac);

#endif