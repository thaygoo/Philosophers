/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:53:47 by huburton          #+#    #+#             */
/*   Updated: 2025/10/27 13:34:48 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	thinking_time(t_philo *philo)
{
	int	margin;

	if (philo->table_data->args.num_philos % 2 == 1)
	{
		margin = philo->table_data->args.time_to_die
			- (philo->table_data->args.time_to_eat
				+ philo->table_data->args.time_to_sleep);
		if (margin > 20)
			usleep(100);
	}
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->table_data->args.num_philos > 1 && philo->id % 2 == 0)
		usleep(100);
	while (!simulation_should_end(philo->table_data))
	{
		philo_eat(philo);
		if (simulation_should_end(philo->table_data))
			break ;
		print_action(philo, "is sleeping");
		precise_usleep(philo->table_data->args.time_to_sleep,
			philo->table_data);
		if (simulation_should_end(philo->table_data))
			break ;
		print_action(philo, "is thinking");
		thinking_time(philo);
	}
	return (NULL);
}
