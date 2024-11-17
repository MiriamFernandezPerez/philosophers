/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:28:05 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/07 21:37:25 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thread_error(int status, t_code code)
{
	if (status == 0)
		return (0);
	if (status == EAGAIN)
		return (ft_msn(AGAIN, 2), 1);
	else if (status == EPERM)
		return (ft_msn(NO_PERM, 2), 1);
	else if (status == EINVAL && code == CREATE)
		return (ft_msn(VALUE_ATTR, 2), 1);
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		return (ft_msn(NO_JOIN, 2), 1);
	else if (status == ESRCH)
		return (ft_msn(SRCH, 2), 1);
	else if (status == EDEADLK)
		return (ft_msn(DEADLK, 2), 1);
	return (0);
}

int	handle_thread(pthread_t *th, void *(*f)(void *), void *data, t_code c)
{
	if (c == CREATE)
	{
		if (thread_error(pthread_create(th, NULL, f, data), c) != 0)
			return (1);
	}
	else if (c == JOIN)
	{
		if (thread_error(pthread_join(*th, NULL), c) != 0)
			return (1);
	}
	else if (c == DETACH)
	{
		if (thread_error(pthread_detach(*th), c) != 0)
			return (1);
	}
	else
		return (ft_msn(TH_CODE, 2), 1);
	return (0);
}
