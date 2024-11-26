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

#include "../inc/philo.h"

void	mutex_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
		ft_msn(VALUE_MUTEX, 2);
	else if (status == EINVAL && code == INIT)
		ft_msn(VALUE_ATTR, 2);
	else if (status == EDEADLK)
		ft_msn(DEAD, 2);
	else if (status == EPERM)
		ft_msn(PERM, 2);
	else if (status == ENOMEM)
		ft_msn(NO_MEM, 2);
	else if (status == EBUSY)
		ft_msn(BUSY, 2);
}

void	handle_mutex(pthread_mutex_t *mutex, t_code code)
{
	if (code == LOCK)
		mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		mutex_error(pthread_mutex_destroy(mutex), code);
	else
		ft_msn(MUT_CODE, 2);
}
