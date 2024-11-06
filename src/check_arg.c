/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirifern <mirifern@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:44:41 by mirifern          #+#    #+#             */
/*   Updated: 2024/11/05 20:44:47 by mirifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*check_input(char *str)
{
	int		i;
	char	*nb;

	i = 0;
	while (ft_isspace(str[i]))
		++str;
	if (str[i] == '+')
		++str;
	else if (str[i] == '-')
		return(ft_msn(NEG, 2), NULL);
    if (!str[i])
        return(ft_msn(NOT_DIG, 2), NULL);
    nb = str;
    return (nb);
}

static	long ft_atol(char *str)
{
	long int	nb;
	int			sign;

	nb = 0;
	sign = 1;
	str = check_input(str);
	if (str == NULL)
		return (-1);
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	if (check_limits(nb))
		return (-1);
	return (sign * nb);
}

int	check_digits(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]))
			i++;
		else
			return (ft_msn(NOT_DIG, 2), EXIT_FAILURE);
	}
	return (0);
}

void	fill_data(t_data *data, char **av, int ac)
{
	data->num_philo = ft_atol(av[1]);
	data->time_die = ft_atol(av[2]) * 1e3;
	data->time_eat = ft_atol(av[3]) * 1e3;
	data->time_sleep = ft_atol(av[4]) * 1e3;
	if (ac == 6)
		data->max_meals = ft_atol(av[5]);
	else
		data->max_meals = -1;
	if (data->time_die < 6e3 || data->time_eat < 6e3 || data->time_sleep < 6e3)
	{
		ft_msn(NO_TIME, 2);
		exit(EXIT_FAILURE);
	}
	printf("num philo %ld\n", data->num_philo);
	printf("time to die %ld\n", data->time_die);
	printf("time to eat %ld\n", data->time_eat);
	printf("time to sleep %ld\n", data->time_sleep);
}

void check_arg(t_data *data, char **av, int ac)
{
	int	i;
	long int	res;

	i = 0;
	i++;
	while (i < ac)
	{
		res = ft_atol(av[i]);
		if (res < 0)
			exit(EXIT_FAILURE);
		else if (res == 0)
		{
			ft_msn(ZERO, 2);
			exit(EXIT_FAILURE);
		}
		if (check_digits(av[i]) == 1)
			exit (EXIT_FAILURE);
		i++;
	}
	fill_data(data, av, ac);
}
