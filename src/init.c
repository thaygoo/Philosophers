/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:01:06 by huburton          #+#    #+#             */
/*   Updated: 2025/10/10 07:53:00 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_current_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write(2, "Error: gettimeofday failed\n", 27);
		return (-1);
	}
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL));
}

static int	init_resources(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->args.num_philos);
	if (!table->philos)
		return (1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->args.num_philos);
	if (!table->forks)
	{
		free(table->philos);
		return (1);
	}
	i = -1;
	while (++i < table->args.num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&table->forks[i]);
			free(table->forks);
			free(table->philos);
			return (1);
		}
	}
	return (0);
}

static void	setup_philos(t_table *table)
{
	int	i;
	int	next;

	i = -1;
	while (++i < table->args.num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_eaten = 0;
		table->philos[i].table_data = table;
		table->philos[i].left_fork = &table->forks[i];
		next = (i + 1) % table->args.num_philos;
		table->philos[i].right_fork = &table->forks[next];
		table->philos[i].last_meal_time = get_current_time_ms();
	}
}

static int	init_sync(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&table->death_lock, NULL))
	{
		pthread_mutex_destroy(&table->print_lock);
		return (1);
	}
	table->simulation_should_end = 0;
	table->start_time = get_current_time_ms();
	if (table->start_time < 0)
		return (1);
	i = -1;
	while (++i < table->args.num_philos)
		table->philos[i].last_meal_time = table->start_time;
	return (0);
}

int	init_simulation(t_table *table)
{
	if (init_resources(table))
		return (1);
	setup_philos(table);
	if (init_sync(table))
	{
		cleanup_resources(table);
		return (1);
	}
	return (0);
}
