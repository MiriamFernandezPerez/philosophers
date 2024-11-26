/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:47:33 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/07 21:35:34 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_malloc(t_data *data)
{
	ft_msn(ERR_MALL, 2);
	ft_free(data);
	exit(EXIT_FAILURE);
}

void	init_forks(t_philo *philo, t_fork *forks, int pos)
{
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo->data->num_philo];
	}
	else
	{
		philo->first_fork = &forks[(pos + 1) % philo->data->num_philo];
		philo->second_fork = &forks[pos];
	}
}

void	init_philo(t_data *data)
{
	int		i;
	t_philo *philo;

	i = 0;
	while (i < data->num_philo)
	{
		philo = data->philos + i; //cambiar por data->philos[i] ej data->philos[i].data = data;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->data = data;
		philo->last_meal_time = philo->data->start_simulation;
		handle_mutex(&data->philos->philo_mutex, INIT);
		init_forks(philo, data->forks, i);
		i++;
	}
}

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->end_simulation = false;
	data->all_threads_ready = false;
	data->all_threads_ready = false;
	data->threads_running_nbr = 0;
	handle_mutex(&data->data_mutex, INIT);
	handle_mutex(&data->write_mutex, INIT);
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		ft_malloc(data);
	data->forks = malloc(sizeof(t_fork) * data->num_philo);
	if (!data->forks)
		ft_malloc(data);
	while (i < data->num_philo)
	{
		handle_mutex(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
		i++;
	}
	init_philo(data);
}
