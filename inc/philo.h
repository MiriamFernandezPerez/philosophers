/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 21:16:56 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/07 21:28:53 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

# define ERR_MALL "Malloc error, please check your computer's memory\n"
# define ERR_ARGS "Wrong arguments quantity, this program require:\n"
# define NUM_PH "1-Number of philosophers\n"
# define TIMES "2-Time to die\n3-Time to eat\n4-Time to sleep\n"
# define OPTIONAL "5-Number of times each philosopher must eat (Optional)\n"
# define NEG "Negative values are not allowed\n"
# define MAX "Number too big, can't be higher than MAX_INT\n"
# define NOT_DIG "Error. Not a digit value\n"
# define ZERO "Number Zero not allowed\n"
# define NO_TIME "Use more than 60ms\n"
# define TH_CODE "Wrong Thread Code\n"
# define MUT_CODE "Wrong Mutex Code\n"
# define VALUE_MUTEX "The value specified by mutex is invalid\n"
# define VALUE_ATTR "The value specified by attr is invalid\n"
# define DEAD "A deadlock would occur is the thread blocked waiting for mutex\n"
# define PERM "The current thread does nor hold a lock on mutex.\n"
# define NO_MEM "The process cannot allocate enough memory to create another mutex\n"
# define BUSY "Mutex is locked\n"
# define AGAIN "No resources to create another thread\n"
# define NO_PERM "The caller does not have appropiate permission\n"
# define NO_JOIN "The value speccified by thread is not joinable\n"
# define SRCH "No thread could be found corresponding to that specified by the given thread ID, thread.\n"
# define DEADLK "A deadlock was detected or the calue of thread specifies the calling thread\n"

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}			t_code;

typedef struct s_data	t_data;

/*typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}				t_fork;*/

typedef struct s_philo
{
	int				id;
	long			total_meals;
	int				full;
	long			last_meal;
	int				left;
	int				right;
	pthread_mutex_t philo_mutex;
	pthread_t		thread_id;
	t_data			*data;
}				t_philo;

struct	s_data
{
	long			num_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			max_meals;
	long			start;
	int				dead;
	pthread_mutex_t	data_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
};

/*philo.c*/
void	ft_free(t_data *data);
int		ft_msn(char *s, int fd);
int		main(int ac, char **av);

/*utils.c*/
int		ft_strlen(char *s);
int		ft_strcmp(char *s1, char *s2);
int		check_limits(long int n);
int		ft_isdigit(char c);
int		ft_isspace(char c);

/*check_arg.c*/
char	*check_input(char *str);
long	ft_atol(char *str);
int		check_digits(char *s);
void	fill_data(t_data *data, char **av, int ac);
void	check_arg(t_data *data, char **av, int ac);

/*handle_mutex.c*/
int		mutex_error(int status, t_code code);
int		handle_mutex(pthread_mutex_t *mutex, t_code code);

/*handle_thread*/
int		thread_error(int status, t_code code);
int		handle_thread(pthread_t *th, void *(*f)(void *), void *data, t_code c);

/*init.c*/
void	ft_malloc(t_data *data);
int		init_philo(t_data *data);
int		init(t_data *data);

/*start.c*/
int		check_dead(t_philo *philo);
void	release_forks(t_philo *philo);
void	*simulation(void *data);
void    start(t_data *data);

/*routine.c*/
int		take_second_fork(t_philo *philo);
int		take_first_fork(t_philo *philo);
int		take_forks(t_philo *philo);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);

/*monitor.c*/
long	current_time();
void	wait_ms(long ms);
void	log_status(t_philo *philo, const char *status);
void	*monitor_philos(t_data *d);
#endif
