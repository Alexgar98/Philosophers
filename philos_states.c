/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:50:24 by alexigar          #+#    #+#             */
/*   Updated: 2024/09/20 13:18:49 by alexigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philosopher *philo, pthread_mutex_t *fork)
{
	struct timeval	tv;
	long long		timestamp;
	long long		current;

	if (!check_death(philo))
	{
		pthread_mutex_lock(fork);
		gettimeofday(&tv, NULL);
		current = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
		timestamp = current - (philo-> start_time);
		pthread_mutex_lock(&(philo-> program -> lock_program));
		philo -> forks_held += 1;
		if (!check_death(philo))
			printf("%llu %d has taken a fork\n", timestamp, philo-> id);
		pthread_mutex_unlock(&(philo-> program -> lock_program));
	}
}

void	p_eat(t_philosopher *philo)
{
	struct timeval	tv;
	long long		timestamp;
	long long		current;

	if (!check_death(philo))
	{
		(philo)-> is_eating = 1;
		gettimeofday(&tv, NULL);
		current = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
		timestamp = current - ((philo)-> start_time);
		pthread_mutex_lock(&(philo-> program -> lock_program));
		printf("%llu %d is eating\n", timestamp, (philo)-> id);
		pthread_mutex_lock(&(philo -> lock_eating));
		(philo)-> times_eaten += 1;
		(philo)-> last_eaten = current;
		pthread_mutex_unlock(&(philo-> program -> lock_program));
		pthread_mutex_unlock(&(philo -> lock_eating));
		usleep((philo)-> time_to_eat * 1000);
		(philo)-> is_eating = 0;
		pthread_mutex_unlock((philo)-> left_fork);
		pthread_mutex_unlock((philo)-> right_fork);
		philo -> forks_held = 0;
	}
	unlock_forks(philo);
}

void	p_sleep(t_philosopher *philo)
{
	struct timeval	tv;
	long long		timestamp;
	long long		current;

	if (!check_death(philo))
	{
		gettimeofday(&tv, NULL);
		current = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
		timestamp = current - (philo-> start_time);
		pthread_mutex_lock(&(philo-> program -> lock_program));
		printf("%llu %d is sleeping\n", timestamp, philo-> id);
		pthread_mutex_unlock(&(philo-> program -> lock_program));
		usleep(philo-> time_to_sleep * 1000);
	}
}

void	p_think(t_philosopher *philo)
{
	struct timeval	tv;
	long long		timestamp;
	long long		current;

	if (!check_death(philo))
	{
		gettimeofday(&tv, NULL);
		current = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
		timestamp = current - (philo-> start_time);
		pthread_mutex_lock(&(philo-> program -> lock_program));
		printf("%llu %d is thinking\n", timestamp, philo-> id);
		pthread_mutex_unlock(&(philo-> program -> lock_program));
	}
}

void	p_die(t_philosopher *philo)
{
	struct timeval	tv;
	long long		timestamp;
	long long		current;

	gettimeofday(&tv, NULL);
	current = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	timestamp = current - (philo-> start_time);
	pthread_mutex_lock(&(philo-> program -> lock_program));
	philo -> dead = 1;
	printf("\x1b[31m%llu %d died\n\x1b[0m", timestamp, philo-> id);
	pthread_mutex_unlock(&(philo-> program -> lock_program));
}
