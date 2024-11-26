/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:54:49 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/08 22:54:50 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->data_mutex, &data->all_threads_ready))
		;
}

long	current_time()
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (ft_msn(GET_TIME, 2), -1);
	return (tv.tv_sec * 1000 + (tv.tv_usec) / 1000);
}

void	log_status(t_philo *philo, t_status status)
{
	long	time;

	time = current_time() - philo->data->start_simulation;
	if (philo->full)
		return ;
	handle_mutex(&philo->data->write_mutex, LOCK);
	if (status == TAKING_FORK && !simulation_finished(philo->data))
		printf("%ld Philosopher %d %s\n", time, philo->id, FORK);
	else if (status == EATING && !simulation_finished(philo->data))
		printf("%ld Philosopher %d %s\n", time, philo->id, EAT);
	else if (status == SLEEPING && !simulation_finished(philo->data))
		printf("%ld Philosopher %d %s\n", time, philo->id, SLEEP);
	else if (status == THINKING && !simulation_finished(philo->data))
		printf("%ld Philosopher %d %s\n", time, philo->id, THINK);
	else if (status == DYING)
		printf("%ld Philosopher %d %s\n", time, philo->id, DIED);
	handle_mutex(&philo->data->write_mutex, UNLOCK);
}

void	wait_ms(long time, t_data *data)
{
	long	start;
	long	elapsed;
	long	res;

	start = current_time();
	while (current_time() - start < time)
	{
		if (simulation_finished(data))
			break ;
		elapsed = current_time() - start;
		res = time - elapsed;
		if (res > 1000)
			usleep(res / 2);
		else
		{
			while (current_time() - start < time)
				;
		}
	}
}

void	stop_sincro(t_philo *philo)
{
	if (philo->data->num_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			wait_ms(1000, philo->data);
	}
	else
	{
		if(philo->id % 2)
			think_philo(philo, 1);
	}
}

void	*simulation(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, current_time());
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	stop_sincro(philo);
	while (!simulation_finished(philo->data))
	{
		if (philo->full)
			break ;
		eat_philo(philo);
		sleep_philo(philo);
		think_philo(philo, 0);
	}
	return (NULL);
}

/* Inicia la simulación */
void	start(t_data *data)
{
	int			i;

	i = 0;
	if (data->nbr_limit_meals == 0)
		return ;
	else if (data->num_philo == 1)
	{
		handle_thread(&data->philos[0].thread_id, one_philo, &data->philos[0], CREATE);
	}
	else
	{
		while (i < data->num_philo)
		{
			handle_thread(&data->philos[i].thread_id, simulation, &data->philos[i], CREATE);
			i++;
		}
	}
	handle_thread(&data->monitor, monitor_philos, data, CREATE);
	data->start_simulation = current_time();
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	i = 0;
	while (i < data->num_philo)
	{
		handle_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	set_bool(&data->data_mutex, &data->end_simulation, true);
	handle_thread(&data->monitor, NULL, NULL, JOIN);
}
