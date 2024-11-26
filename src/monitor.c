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

#include "../inc/philo.h"

bool philo_died(t_philo *philo)
{
	long	time;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	time = current_time() - philo->data->start_simulation + get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->data->time_die;
	if (time > t_to_die)
	{
		printf("time %ld t_tp_die %ld\n", time, t_to_die);
		return (true);
	}
	return (false);
}

void	increase_long(pthread_mutex_t *mutex, long *value)
{
	handle_mutex(mutex, LOCK);
	(*value)++;
	handle_mutex(mutex, UNLOCK);
}

bool	all_threads_running(pthread_mutex_t *mutex, long *threads, long philo_nbr)
{
	bool	res;

	res = false;
	handle_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		res = true;
	handle_mutex(mutex, UNLOCK);
	return (res);
}

/* Monitoriza el estado de los filósofos */
void	*monitor_philos(void *data)
{
	int		i;
	t_data *d;

	d = (t_data *)data;
	while (!all_threads_running(&d->data_mutex, &d->threads_running_nbr, d->num_philo))
		; 
	while(!simulation_finished(d))
	{
		i = 0;
		while (i < d->num_philo && !simulation_finished(data))
		{
			if (philo_died(d->philos + i))
			{
				set_bool(&d->data_mutex, &d->end_simulation, true);
				log_status(d->philos + i, DYING);
			}
			i++;
		}
	}
	return (NULL);
}
