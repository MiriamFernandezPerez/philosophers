/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:44:54 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/07 21:31:33 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void ft_free(t_data *data)
{
	t_philo	*philo;
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		philo = data->philos + i;
		handle_mutex(&philo->philo_mutex, DESTROY);
		i++;
	}
	handle_mutex(&data->write_mutex, DESTROY);
	handle_mutex(&data->data_mutex, DESTROY);
	free(data->philos);
	free(data->forks);
}

//Write msn function
int	ft_msn(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		ft_msn(ERR_ARGS, 2);
		ft_msn(NUM_PH, 2);
		ft_msn(TIMES, 2);
		return (ft_msn(OPTIONAL, 2), EXIT_FAILURE);
	}
	else
	{
		if (check_arg(&data, av, ac) == EXIT_SUCCESS)
		{
			init_data(&data);
			start(&data);
			ft_free(&data);
		}
	}
	return (0);
}
