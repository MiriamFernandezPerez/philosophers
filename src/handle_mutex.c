/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:08:16 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/07 21:39:09 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_error(int status, t_code code)
{
	if (status == 0)
		return (0);
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
		return(ft_msn(VALUE_MUTEX, 2), 1);
	else if (status == EINVAL && code == INIT)
		return (ft_msn(VALUE_ATTR, 2), 1);
	else if (status == EDEADLK)
		return (ft_msn(DEAD, 2), 1);
	else if (status == EPERM)
		return (ft_msn(PERM, 2), 1);
	else if (status == ENOMEM)
		return (ft_msn(NO_MEM, 2), 1);
	else if (status == EBUSY)
		return (ft_msn(BUSY, 2), 1);
	return (0);
}

int	handle_mutex(pthread_mutex_t *mutex, t_code code)
{
	if (code == LOCK)
	{
		if (mutex_error(pthread_mutex_lock(mutex), code) != 0)
			return (1);
	}
	else if (code == UNLOCK)
	{
		if (mutex_error(pthread_mutex_unlock(mutex), code) != 0)
			return (1);
	}
	else if (code == INIT)
	{
		if (mutex_error(pthread_mutex_init(mutex, NULL), code) != 0)
			return (1);
	}
	else if (code == DESTROY)
	{
		if (mutex_error(pthread_mutex_destroy(mutex), code) != 0)
			return (1);
	}
	else
		return(ft_msn(MUT_CODE, 2), 1);
	return (0);
}
