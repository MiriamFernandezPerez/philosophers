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

void	ft_malloc(t_data *data)
{
	ft_msn(ERR_MALL, 2);
	ft_free(data);
	exit(1);
}

int	init_philo(t_data *data)
{
	int		i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philo);
	if (!data->philos)
		ft_malloc(data);
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].total_meals = 0;
		data->philos[i].data = data;
		data->philos[i].full = -1;
		data->philos[i].last_meal = 0;
		data->philos[i].left = data->philos[i].id - 1;
		if (data->num_philo > 1)
			data->philos[i].right = data->philos[i].id % data->num_philo;
		data->philos[i].thread_id = -1;
		if (handle_mutex(&data->philos[i].philo_mutex, INIT) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		ft_malloc(data);
	while (i < data->num_philo)
	{
		if (handle_mutex(&data->forks[i], INIT) == 1)
		{
			printf("error 1\n");
			return (1);
		}
		i++;
	}
	if (handle_mutex(&data->data_mutex, INIT) == 1)
	{
		printf("error 2\n");
		return (1);
	}
	if (init_philo(data) == 1)
	{
		printf("error 3\n");
		return (1);
	}
	return (0);
}
