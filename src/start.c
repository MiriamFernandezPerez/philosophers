/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:54:49 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/08 22:54:50 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *simulation(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    printf("comienza la simulacion\n");
    check_sincronize();
}

void    start(t_data *data)
{
    int i;

    i = 0;
    if (data->max_meals == 0)
        return ;
    else if (data->num_philo == 1)
        printf("SOlo un philo??\n");
    else
    {
        while (i < data->num_philo)
        {
            handle_thread(&data->philos[i].thread_id, simulation,
                &data->philos[i], CREATE);
            i++;
        }
    }
}