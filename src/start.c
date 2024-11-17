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

#include "philo.h"

/* Desbloqueo los mutex de los tenedores */
void	release_forks(t_philo *philo)
{
	handle_mutex(&(philo->data->forks[philo->left]), UNLOCK);
	handle_mutex(&(philo->data->forks[philo->right]), UNLOCK);
}

int	check_dead(t_philo *philo)
{
	long	time;

	time = current_time();
	handle_mutex(&philo->data->data_mutex, LOCK);
	if (philo->data->dead == 1)
	{
		handle_mutex(&philo->data->data_mutex, UNLOCK);
		return (1);
	}
	if (time - philo->last_meal > philo->data->time_die)
	{
		philo->data->dead = 1;
		//printf("%ld %d died\n", time - philo->data->start, philo->id);
		handle_mutex(&philo->data->data_mutex, UNLOCK);
		return (1);
	}
	handle_mutex(&philo->data->data_mutex, UNLOCK);
	return (0);
}

/* Simulación de cada filósofo */
void	*simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (take_forks(philo) == 0)
		{
			log_status(philo, "is eating");
			philo->last_meal = current_time();
			//wait_ms(philo->data->time_eat);
			release_forks(philo);
			log_status(philo, "is sleeping");
			wait_ms(philo->data->time_sleep);
			log_status(philo, "is thinking");

		}
			continue ;

		pthread_mutex_unlock(&philo->data->data_mutex);
		wait_ms(philo->data->time_eat);
		release_forks(philo);
		log_status(philo, "is sleeping");
		wait_ms(philo->data->time_sleep);
		log_status(philo, "is thinking");
	}
	pthread_exit(NULL);
}

/* Inicia la simulación */
void	start(t_data *data)
{
	int			i;

	i = 0;
	if (data->max_meals == 0)
		return ;
	/* Creo los hilos para los filósofos */
	while (i < data->num_philo)
	{
		data->philos[i].last_meal = data->start;
		handle_thread(&data->philos[i].thread_id, simulation, &data->philos[i], CREATE);
		i++;
	}
	monitor_philos(data);
	i = 0;
	/* Espero que todos los filósofos terminen */
	while (i < data->num_philo)
	{
		handle_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}
