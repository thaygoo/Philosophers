/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:45:25 by huburton          #+#    #+#             */
/*   Updated: 2025/08/28 12:55:21 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	fill_table(t_args *args, char **av)
{
	args->num_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
}

int	parse_arg(t_args *args, char **av, int ac)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Usage: ./philo num_philos ", 26);
		write(2, "time_die time_eat time_sleep [num_eat]\n", 39);
		return (1);
	}
	fill_table(args, av);
	if (ac == 6)
		args->num_times_to_eat = ft_atoi(av[5]);
	else
		args->num_times_to_eat = -1;
	if (args->num_philos <= 0 || args->num_philos > 200
		|| args->time_to_die < 60 || args->time_to_eat < 60
		|| args->time_to_sleep < 60)
	{
		write(2, "Error: Invalid argument values.\n", 32);
		return (1);
	}
	if (ac == 6 && args->num_times_to_eat <= 0)
	{
		write(2, "Error: Invalid value for num_times_to_eat.\n", 43);
		return (1);
	}
	return (0);
}
