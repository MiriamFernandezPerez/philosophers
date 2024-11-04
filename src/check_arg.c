#include "philo.h"

static char	*check_input(char *str)
{
	int		len;
	int		i;
	char	*nb;

	len = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		ft_msn(NEG, 2);
    if (!ft_str[i])
        ft_msn(NOT_DIG, 2);
    nb = str[i];
    return (str);
}

static	long ft_atol(char *str)
{
	long	num;

	num = 0;
	str = check_input(str);
    return (0);
}

void check_arg(t_data *data, char **av)
{
    data->num_philo = ft_atol(av[1]);
}