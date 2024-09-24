/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:34:41 by alexigar          #+#    #+#             */
/*   Updated: 2024/09/20 13:18:51 by alexigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosopher	*init_philo(t_program *program, int i)
{
	t_philosopher	*philo;

	philo = malloc(sizeof(t_philosopher));
	if (!philo)
		return (free_philos(program));
	philo -> id = i + 1;
	philo -> time_to_die = program -> time_to_die;
	philo -> time_to_eat = program -> time_to_eat;
	philo -> time_to_sleep = program -> time_to_sleep;
	philo -> max_meals = program -> max_meals;
	philo -> times_eaten = 0;
	philo -> last_eaten = 0;
	philo -> dead = 0;
	philo -> is_eating = 0;
	philo -> forks_held = 0;
	philo -> left_fork = &(program -> forks[i]);
	if ((philo -> id + 1) <= program -> n_philos)
		philo -> right_fork = &(program -> forks[i + 1]);
	else if (program -> n_philos > 1)
		philo -> right_fork = &(program -> forks[0]);
	else
		philo -> right_fork = philo -> left_fork;
	return (philo);
}

t_philosopher	**init_philos(t_program *program)
{
	int				i;
	t_philosopher	**philos;

	i = 0;
	philos = malloc(sizeof(t_philosopher *) * (program -> n_philos + 1));
	if (!philos)
		return (NULL);
	while (i < program -> n_philos)
	{
		philos[i] = init_philo(program, i);
		if (!philos[i])
			return (free_philos(program));
		if (pthread_mutex_init(&(philos[i]-> lock_times_eaten), NULL)
			|| pthread_mutex_init(&(philos[i]-> lock_eating), NULL))
			return (free_philos(program));
		philos[i]-> program = program;
		i++;
	}
	return (philos);
}

t_program	*init_program(int argc, char **argv)
{
	t_program	*program;

	program = malloc(sizeof(t_program));
	if (!program)
		return (NULL);
	if (pthread_mutex_init(&(program -> lock_program), NULL)
		|| pthread_mutex_init(&(program -> lock_dead), NULL))
	{
		free(program);
		return (NULL);
	}
	program -> dead = 0;
	program -> n_philos = ft_atoi(argv[1]);
	if (program -> n_philos > 200 || program -> n_philos < 1)
		error_msg2(program);
	program -> time_to_die = ft_atoi(argv[2]);
	program -> time_to_eat = ft_atoi(argv[3]);
	program -> time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program -> max_meals = ft_atoi(argv[5]);
	else
		program -> max_meals = -1;
	return (program);
}

t_program	*prepare_program(int argc, char **argv)
{
	t_program	*program;

	program = init_program(argc, argv);
	if (!program)
		return (NULL);
	if (program -> n_philos > 200 || program -> n_philos < 1)
		return (program);
	program -> forks = init_forks(program);
	if (!(program -> forks))
	{
		free(program);
		return (NULL);
	}
	program -> philos = init_philos(program);
	if (!(program -> philos))
	{
		destroy_forks(program -> forks);
		free(program);
		return (NULL);
	}
	return (program);
}

void	unlock_forks(t_philosopher *philo)
{
	if (philo -> forks_held > 0)
		pthread_mutex_unlock((philo)-> left_fork);
	if (philo -> forks_held > 1)
		pthread_mutex_unlock((philo)-> right_fork);
}
