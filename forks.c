/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:24:13 by alexigar          #+#    #+#             */
/*   Updated: 2024/09/20 13:11:20 by alexigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_philosopher *philo)
{
	pthread_mutex_destroy(&philo -> lock_times_eaten);
	pthread_mutex_destroy(&philo -> lock_eating);
}

void	kill_all(t_program *program)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(program -> lock_dead));
	program -> dead = 1;
	pthread_mutex_unlock(&(program -> lock_dead));
	while (i < program -> n_philos)
	{
		program -> philos[i]-> dead = 1;
		i++;
	}
	usleep((program -> time_to_eat + program -> time_to_sleep) * 1000);
}

void	destroy_forks(pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (!pthread_mutex_destroy(&forks[i]))
		i++;
	free(forks);
}

pthread_mutex_t	*init_forks(t_program *program)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * ((program -> n_philos) + 1));
	if (!forks)
		return (NULL);
	while (i < program -> n_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			destroy_forks(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	check_death(t_philosopher *philo)
{
	int	to_return;

	to_return = 0;
	pthread_mutex_lock(&(philo-> program -> lock_dead));
	if (philo -> program -> dead)
		to_return = 1;
	pthread_mutex_unlock(&(philo-> program -> lock_dead));
	return (to_return);
}
