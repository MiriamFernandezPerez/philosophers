
#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

//Write msn function
int	ft_msn(char *s, int fd)
{
	if (write(fd, s, ft_strlen(s)) == -1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
