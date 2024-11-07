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

#include "philo.h"

void	free_data(t_data *data)
{
	(void)data;
}

void	ft_malloc(t_data *data)
{
	ft_msn(ERR_MALL, 2);
	free_data(data, 1);
	exit(1);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->max_meals = 0;
		philo->full = -1;
		philo->last_meal = 0;
		philo->left = NULL;
		philo->right = NULL;
		philo->thread_id = NULL;
		i++;
	}
}

void	init(t_data *data)
{
	int	i;

	i = 0;
	data->end = -1;
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
	}
	init_philo(data);
}
