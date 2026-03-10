/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:29:44 by huburton          #+#    #+#             */
/*   Updated: 2025/10/27 12:35:30 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	timestamp(t_table *table)
{
	return (get_current_time_ms() - table->start_time);
}

int	simulation_should_end(t_table *table)
{
	int	flag;

	pthread_mutex_lock(&table->death_lock);
	flag = table->simulation_should_end;
	pthread_mutex_unlock(&table->death_lock);
	return (flag);
}

void	print_action(t_philo *philo, const char *action)
{
	long long	time;

	pthread_mutex_lock(&philo->table_data->print_lock);
	if (!simulation_should_end(philo->table_data))
	{
		time = timestamp(philo->table_data);
		printf("%lld %d %s\n", time, philo->id, action);
	}
	pthread_mutex_unlock(&philo->table_data->print_lock);
}

void	precise_usleep(long long duration_ms, t_table *table)
{
	long long	start;
	long long	elapsed;
	long long	remaining;

	start = get_current_time_ms();
	while (!simulation_should_end(table))
	{
		elapsed = get_current_time_ms() - start;
		if (elapsed >= duration_ms)
			break ;
		remaining = duration_ms - elapsed;
		if (remaining > 10)
			usleep((remaining / 2) * 1000);
		else if (remaining > 1)
			usleep(500);
		else
			usleep(100);
	}
}
