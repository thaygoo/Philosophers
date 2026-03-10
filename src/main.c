/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:29:41 by huburton          #+#    #+#             */
/*   Updated: 2025/10/27 13:34:48 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_resources(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = 0;
		while (i < table->args.num_philos)
			pthread_mutex_destroy(&table->forks[i++]);
	}
	pthread_mutex_destroy(&table->print_lock);
	pthread_mutex_destroy(&table->death_lock);
	if (table->forks)
	{
		free(table->forks);
		table->forks = NULL;
	}
	if (table->philos)
	{
		free(table->philos);
		table->philos = NULL;
	}
}

int	main(int ac, char **av)
{
	t_table	table_data;

	if (parse_arg(&table_data.args, av, ac))
		return (1);
	if (init_simulation(&table_data))
	{
		write(2, "Error: Failed to initialize simulation\n", 39);
		return (1);
	}
	if (start_threads(&table_data))
	{
		write(2, "Error: Failed to start threads\n", 31);
		cleanup_resources(&table_data);
		return (1);
	}
	cleanup_resources(&table_data);
	return (0);
}

//gcc -Wall -Wextra -Werror -Iincludes -fsanitize=thread -g src/*.c 
//	-lpthread -o philo_tsan && ./philo_tsan 5 800 200 200 3

//valgrind --tool=helgrind ./philo 5 800 200 200 3

//valgrind --leak-check=full --show-leak-kinds=all 
//	--track-origins=yes ./philo 5 800 200 200 3
