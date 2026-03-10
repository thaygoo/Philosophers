/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huburton <huburton@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:29:44 by huburton          #+#    #+#             */
/*   Updated: 2025/10/23 11:54:55 by huburton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

// ARGUMENTS :

typedef struct s_args
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_to_eat;
}	t_args;

struct	s_table;

typedef struct s_philo
{
	int					id;
	pthread_t			thread_id;
	long long			last_meal_time;
	int					meals_eaten;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_table		*table_data;
}	t_philo;

// Structure pour les données globales de la table/simulation
typedef struct s_table
{
	t_args			args;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	long long		start_time;
	int				simulation_should_end;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
}	t_table;

// UTILS :

int			ft_atoi(const char *str);
int			parse_arg(t_args *args, char **av, int ac);
long long	get_current_time_ms(void);
long long	timestamp(t_table *table);
void		print_action(t_philo *philo, const char *action);
void		precise_usleep(long long duration_ms, t_table *table);
int			init_simulation(t_table *table);
int			start_threads(t_table *table);

// Routines des threads
void		*philosopher_routine(void *arg);
void		*monitor_routine(void *arg);
void		philo_eat(t_philo *philo);

// Gestion de l'état de la simulation
int			simulation_should_end(t_table *table);
void		cleanup_resources(t_table *table);

#endif