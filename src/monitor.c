/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 23:31:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/14 23:31:27 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Obtiene el tiempo actual y lo convierte a milisegundos */
long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	wait_ms(long ms)
{
	usleep(ms);
}

/* Imprime el estado de los filósofos */
void	log_status(t_philo *philo, const char *status)
{
	long	time;

	time = current_time() - philo->data->start;
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->dead == 0)
		printf("%ld Philosopher %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->data_mutex);
}

int check_meals(t_data *d, int i)
{
	if (d->max_meals != -1 && d->philos[i].total_meals == d->max_meals)
	{
		handle_mutex(&d->data_mutex, LOCK);
		d->philos[i].full = 1;
		handle_mutex(&d->data_mutex, UNLOCK);
		handle_mutex(&d->philos[i].philo_mutex, UNLOCK);
		i++;
		//continue ;
	}
	return (0);
}

/* Monitoriza el estado de los filósofos */
void	*monitor_philos(t_data *d)
{
	int		i;

	while (1)
	{
		i = 0;
		while (i < d->num_philo)
		{
			handle_mutex(&d->philos[i].philo_mutex, LOCK);
			if (current_time() - d->philos[i].last_meal > d->time_die)
			{
				handle_mutex(&d->data_mutex, LOCK);
				log_status(&d->philos[i], "died");
				d->dead = 1;
				handle_mutex(&d->data_mutex, UNLOCK);
				handle_mutex(&d->philos[i].philo_mutex, UNLOCK);
				break ;
			}
			pthread_mutex_unlock(&d->data_mutex);
			if (check_meals(d, i))
				break ;
			i++;
		}
		//wait_ms(10);
	}
	//pthread_exit(NULL);
}
