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
	printf("CURRENT TIME %ld\n", (tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	wait_ms(long ms)
{
	usleep(ms * 1000);
}

/* Imprime el estado de los filósofos */
void	log_status(t_philo *philo, const char *status)
{
	long	time;

	time = current_time() - philo->data->start;
	printf("DATA-STAR %ld\n", philo->data->start);
	printf("TIME %ld\n", time);
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->dead == 0)
		printf("%ld %d %s\n", time, philo->id, status);
	printf("TIME %ld\n", time);
	pthread_mutex_unlock(&philo->data->data_mutex);
}

/* Monitoriza el estado de los filósofos */
void	*monitor_philos(void *data)
{
	int		i;
	t_data	*d;

	i = 0;
	d = (t_data *)data;
	while (1)
	{
		pthread_mutex_lock(&d->data_mutex);
		if (d->dead == 1)
		{
			pthread_mutex_unlock(&d->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&d->data_mutex);
		while (i < d->num_philo)
		{
			pthread_mutex_lock(&d->data_mutex);
			if (current_time() - d->philos[i].last_meal > d->time_die)
			{
				log_status(&d->philos[i], "died");
				d->dead = 1;
				pthread_mutex_unlock(&d->data_mutex);
				break ;
			}
			pthread_mutex_unlock(&d->data_mutex);
			i++;
		}
		wait_ms(10);
	}
	pthread_exit(NULL);
}
