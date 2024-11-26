/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:41:13 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/25 22:44:15 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	handle_mutex(mutex, LOCK);
	*dest = value;
	handle_mutex(mutex, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	res;
	handle_mutex(mutex, LOCK);
	res = *value;
	handle_mutex(mutex, UNLOCK);
	return (res);
}

void	set_long(pthread_mutex_t *mutex, long int *dest, long int value)
{
	handle_mutex(mutex, LOCK);
	*dest = value;
	handle_mutex(mutex, UNLOCK);
}

bool	get_long(pthread_mutex_t *mutex, long int *value)
{
	long	res;
	handle_mutex(mutex, LOCK);
	res = *value;
	handle_mutex(mutex, UNLOCK);
	return (res);
}

bool	simulation_finished(t_data *data)
{
	return (get_bool(&data->data_mutex, &data->end_simulation));
}
