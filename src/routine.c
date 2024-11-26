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

#include "../inc/philo.h"


void	think_philo (t_philo *philo, int flag)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (flag == 0)
		log_status(philo, THINKING);
	if(philo->data->num_philo % 2 == 0)
		return ;
	t_eat = philo->data->time_eat;
	t_sleep = philo->data->time_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	wait_ms(t_think * 0.42, philo->data);
}

void	sleep_philo(t_philo *philo)
{
	log_status(philo, SLEEPING);
	wait_ms(philo->data->time_sleep, philo->data);
}

void	eat_philo(t_philo *philo)
{
	handle_mutex(&philo->first_fork->fork, LOCK);
	log_status(philo, TAKING_FORK);
	handle_mutex(&philo->second_fork->fork, LOCK);
	log_status(philo, TAKING_FORK);
	set_long(&philo->philo_mutex, &philo->last_meal_time, current_time());
	philo->meals_counter++;
	log_status(philo, EATING);
	wait_ms(philo->data->time_eat, philo->data);
	if (philo->data->nbr_limit_meals > 0 && philo->meals_counter == philo->data->nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	handle_mutex(&philo->first_fork->fork, UNLOCK);
	handle_mutex(&philo->second_fork->fork, UNLOCK);
}

void	*one_philo(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, current_time());
	increase_long(&philo->data->data_mutex, &philo->data->threads_running_nbr);
	log_status(philo, TAKING_FORK);
	while (!simulation_finished(philo->data))
		usleep(200);
	return (NULL);
}