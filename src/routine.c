/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:51:13 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/17 20:51:15 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_second_fork(t_philo *philo)
{
	if (philo->id % 2)
		handle_mutex(&philo->data->forks[philo->left], LOCK);
	else
		handle_mutex(&philo->data->forks[philo->right], LOCK);
	log_status(philo, "has taken a fork");
	return (0);
}

/* Intento coger el primer tenedor de forma segura, evitando deadlock */
int	take_first_fork(t_philo *philo)
{
	if (philo->id % 2)
		handle_mutex(&philo->data->forks[philo->right], LOCK);
	else
		handle_mutex(&philo->data->forks[philo->left], LOCK);
	log_status(philo, "has taken a fork");
	return (0);
}

int take_forks(t_philo *philo)
{
	if (take_first_fork(philo) != 0)
		return (1);
	if (philo->data->num_philo == 1)
	{
		wait_ms(philo->data->time_die);
	}
	if (take_second_fork(philo) != 0)
		return (1);
	if (check_dead(philo) == 1)
	{
		handle_mutex(&(philo->data->forks[philo->left]), UNLOCK);
		handle_mutex(&(philo->data->forks[philo->right]), UNLOCK);
		return (1);
	}
	return (0);
}
int	philo_eat(t_philo *philo)
{
	log_status(philo, "is eating");
	handle_mutex(&(philo->philo_mutex), LOCK);
	philo->last_meal = current_time();
	handle_mutex(&(philo->philo_mutex), UNLOCK);
	wait_ms(philo->data->time_eat);
	handle_mutex(&(philo->philo_mutex), LOCK);
	philo->total_meals++;
	handle_mutex(&(philo->philo_mutex), UNLOCK);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	log_status(philo, "is sleeping");
	wait_ms(philo->data->time_sleep);
	return (0);
}
