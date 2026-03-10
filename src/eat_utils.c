/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:50:00 by huburton          #+#    #+#             */
/*   Updated: 2025/10/27 13:31:06 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	handle_single_philo(t_philo *philo, pthread_mutex_t *first_fork)
{
	while (!simulation_should_end(philo->table_data))
		usleep(100);
	pthread_mutex_unlock(first_fork);
}

static void	acquire_forks(t_philo *philo, pthread_mutex_t **first_fork,
						pthread_mutex_t **second_fork)
{
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
	else
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	long long		time;

	acquire_forks(philo, &first_fork, &second_fork);
	pthread_mutex_lock(first_fork);
	print_action(philo, "has taken a fork");
	if (philo->table_data->args.num_philos == 1)
	{
		handle_single_philo(philo, first_fork);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print_action(philo, "has taken a fork");
	time = get_current_time_ms();
	pthread_mutex_lock(&philo->table_data->death_lock);
	philo->last_meal_time = time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->table_data->death_lock);
	print_action(philo, "is eating");
	precise_usleep(philo->table_data->args.time_to_eat, philo->table_data);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}
