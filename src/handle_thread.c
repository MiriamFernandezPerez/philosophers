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

void	thread_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		ft_msn(AGAIN, 2);
	else if (status == EPERM)
		ft_msn(NO_PERM, 2);
	else if (status == EINVAL && code == CREATE)
		ft_msn(VALUE_ATTR, 2);
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		ft_msn(NO_JOIN, 2);
	else if (status == ESRCH)
		ft_msn(SRCH, 2);
	else if (status == EDEADLK)
		ft_msn(DEADLK, 2);
}

void	handle_thread(pthread_t *thread, void *(*foo)(void *), void *data, t_code code)
{
	if (code == CREATE)
		thread_error(pthread_create(thread, NULL, foo, data), code);
	else if (code == JOIN)
		thread_error(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		thread_error(pthread_detach(*thread), code);
	else
		ft_msn(TH_CODE, 2);
}
