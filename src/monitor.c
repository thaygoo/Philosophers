/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 15:00:00 by huburton          #+#    #+#             */
/*   Updated: 2025/10/27 13:31:06 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	set_simulation_end_flag(t_table *table)
{
	pthread_mutex_lock(&table->death_lock);
	table->simulation_should_end = 1;
	pthread_mutex_unlock(&table->death_lock);
}

static int	check_death_condition(t_table *table)
{
	int			i;
	long long	now;
	long long	last;

	now = get_current_time_ms();
	i = 0;
	while (i < table->args.num_philos)
	{
		pthread_mutex_lock(&table->death_lock);
		last = table->philos[i].last_meal_time;
		pthread_mutex_unlock(&table->death_lock);
		if (now < 0 || now - last > table->args.time_to_die)
		{
			set_simulation_end_flag(table);
			pthread_mutex_lock(&table->print_lock);
			printf("%lld %d died\n", timestamp(table), table->philos[i].id);
			pthread_mutex_unlock(&table->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_eaten_condition(t_table *table)
{
	int	i;
	int	all_done;

	if (table->args.num_times_to_eat < 0)
		return (0);
	pthread_mutex_lock(&table->death_lock);
	all_done = 1;
	i = 0;
	while (i < table->args.num_philos)
	{
		if (table->philos[i].meals_eaten < table->args.num_times_to_eat)
		{
			all_done = 0;
			break ;
		}
		i++;
	}
	pthread_mutex_unlock(&table->death_lock);
	if (all_done)
	{
		usleep(table->args.time_to_eat * 1000);
		set_simulation_end_flag(table);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!simulation_should_end(table))
	{
		if (check_death_condition(table) || check_all_eaten_condition(table))
			break ;
		usleep(1000);
	}
	return (NULL);
}
