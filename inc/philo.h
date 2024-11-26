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
# include <stdbool.h>

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
# define GET_TIME "Get Time of day function failed\n"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DIED "died\n"

/* Define colors*/
# define RST "\33[0m" //Default
# define RED "\33[1;31m" //Red
# define GRN "\33[1;32m" //Green
# define YEL "\33[1;33m" //Yellow
# define BLU "\33[1;34m" //Blue
# define CYA "\33[1;35m" //Cyan
# define WHT "\33[1;36m" //White

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKING_FORK,
	DYING,
}			t_status;

typedef enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_code;

typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time;

typedef struct s_data	t_data;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}				t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	bool			full; 
	long			last_meal_time; 
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_t		thread_id;
	pthread_mutex_t	philo_mutex;
	t_data			*data;
	}				t_philo;

struct	s_data
{
	long			num_philo;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	long			nbr_limit_meals;
	long			start_simulation;
	bool			end_simulation;
	bool			all_threads_ready;
	long			threads_running_nbr;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t write_mutex;
	pthread_t		monitor;
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
int		fill_data(t_data *data, char **av, int ac);
int		check_arg(t_data *data, char **av, int ac);

/*handle_mutex.c*/
void	mutex_error(int status, t_code code);
void	handle_mutex(pthread_mutex_t *mutex, t_code code);

/*handle_thread*/
void	thread_error(int status, t_code code);
void	handle_thread(pthread_t *th, void *(*f)(void *), void *data, t_code c);

/*init.c*/
void	ft_malloc(t_data *data);
void	init_forks(t_philo *philo, t_fork *forks, int pos);
void	init_philo(t_data *data);
void	init_data(t_data *data);

/*start.c*/
void	wait_all_threads(t_data *data);
long	current_time();
void	log_status(t_philo *philo, t_status status);
void	wait_ms(long time, t_data *data);
void	*simulation(void *data);
void	start(t_data *data);

/*routine.c*/
void	think_philo(t_philo *philo, int flag);
void	sleep_philo(t_philo *philo);
void	eat_philo(t_philo *philo);
void	*one_philo(void *data);

/*end_simulation.c*/
void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
bool	get_bool(pthread_mutex_t *mutex, bool *value);
void	set_long(pthread_mutex_t *mutex, long int *dest, long int value);
bool	get_long(pthread_mutex_t *mutex, long int *value);
bool	simulation_finished(t_data *data);

/*monitor.c*/
bool	philo_died(t_philo *philo);
void	increase_long(pthread_mutex_t *mutex, long *value);
bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr);
void	*monitor_philos(void *data);
#endif
