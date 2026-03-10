/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:53:47 by huburton          #+#    #+#             */
/*   Updated: 2025/10/10 07:53:00 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	join_philos(t_table *table, int count)
{
	while (count > 0)
		pthread_join(table->philos[--count].thread_id, NULL);
}

static int	create_philosopher_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args.num_philos)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL,
				philosopher_routine, &table->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	start_threads(t_table *table)
{
	int			i;
	pthread_t	monitor_id;

	table->start_time = get_current_time_ms();
	if (table->start_time < 0)
	{
		write(2, "Error: start time\n", 19);
		return (1);
	}
	if (create_philosopher_threads(table))
		return (1);
	i = table->args.num_philos;
	if (pthread_create(&monitor_id, NULL, monitor_routine, table) != 0)
		return (1);
	join_philos(table, i);
	pthread_join(monitor_id, NULL);
	return (0);
}
