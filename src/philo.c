/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:44:54 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/05 20:44:56 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

//Write msn function
int	ft_msn(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

int main(int ac, char **av)
{
    t_data  data;

    if (ac < 5 || ac > 6)
        return (ft_msn(ERR_ARGS, 2), 1);
    else
    {
        check_arg(&data, av, ac);
        //init(&data);
        //start(&data);
        //ft_free(&data);
    }
    char *s;
    s = malloc(sizeof(char *));
    if (!s)
        return(ft_msn(strerror(errno), 2), 1);
    free(s);
    return (0);
}
