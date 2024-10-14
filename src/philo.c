
#include "philo.h"

int main(int ac, char **av)
{
    int i;

    i = 0;
    (void)av;
    (void)i;
    if (ac != 5)
    {
        return (ft_msn(ERR_ARGS, 2));
    }
    return (0);
}
