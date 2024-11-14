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

/* Bloquea los tenedores de forma segura, evitando deadlock */
void	take_forks(t_philo *philo)
{
	if (philo->left->fork_id < philo->right->fork_id)
	{
		pthread_mutex_lock(&philo->left->fork);
		log_status(philo, "has taken a fork");
		//TODO
		//VERIFICAR SI TENGO EL OTRO TENEDOR Y COMER
		//SI NO LO TENGO, LIBERO EL TENEDOR QUE TENGO
		//Y VUELVO A INTENTAR TOMAR LOS TENEDORES
		//PARA EVITAR DEADLOCK
		pthread_mutex_unlock(&philo->left->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->right->fork);
		log_status(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->right->fork);
	}
}

/* Desbloqueo los mutex de los tenedores */
void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_unlock(&philo->right->fork);
}

/* Simulación de cada filósofo */
void	*simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->dead == 1)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		take_forks(philo);
		pthread_mutex_lock(&philo->data->data_mutex);
		log_status(philo, "is eating");
		philo->last_meal = current_time();
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
	pthread_t	monitor;

	i = 0;
	if (data->max_meals == 0)
		return ;
	else if (data->num_philo == 1)
	{
		printf("Solo un filósofo\n"); // TODO
		return ;
	}
	/* Creo los hilos para los filósofos */
	while (i < data->num_philo)
	{
		data->philos[i].last_meal = data->start;
		handle_thread(&data->philos[i].thread_id, simulation, &data->philos[i], CREATE);
		i++;
	}
	/* Creo el hilo de monitoreo de filósofos */
	handle_thread(&monitor, monitor_philos, data, CREATE);
	i = 0;
	/* Espero que todos los filósofos terminen */
	while (i < data->num_philo)
	{
		handle_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	// Espero que el hilo de monitoreo termine
	handle_thread(&monitor, NULL, NULL, JOIN);
}
