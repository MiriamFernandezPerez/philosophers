
#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;

    if (ac < 5 || ac > 6)
        return (ft_msn(ERR_ARGS, 2), 1);
    else
    {
        check_arg(&data, av);
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
