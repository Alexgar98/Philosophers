/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:07:20 by alexigar          #+#    #+#             */
/*   Updated: 2024/09/19 13:02:22 by alexigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *phil)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)phil;
	if (philo -> id % 2 == 0)
		usleep(1000);
	while (1)
	{
		take_fork(philo, philo -> left_fork);
		take_fork(philo, philo -> right_fork);
		p_eat(philo);
		pthread_mutex_lock(&(philo-> program -> lock_program));
		if (philo -> times_eaten == philo -> max_meals)
			break ;
		pthread_mutex_unlock(&(philo-> program -> lock_program));
		p_sleep(philo);
		p_think(philo);
		pthread_mutex_lock(&(philo-> program -> lock_program));
		if (philo -> program -> dead)
			break ;
		pthread_mutex_unlock(&(philo-> program -> lock_program));
	}
	pthread_mutex_unlock(&(philo-> program -> lock_program));
	destroy_mutex(philo);
	return (NULL);
}

int	check_dead(t_program **program, int i)
{
	struct timeval	tv;
	long long		current;

	gettimeofday(&tv, NULL);
	current = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	if ((current - (*program)-> philos[i]-> last_eaten)
		>= ((*program)-> time_to_die)
		&& !((*program)-> philos[i]-> is_eating))
	{
		p_die((*program)-> philos[i]);
		kill_all(*program);
		return (1);
	}
	return (0);
}

void	*philos_control(void *prog)
{
	int				i;
	t_program		*program;
	int				finished;

	finished = 0;
	program = (t_program *)prog;
	while (1)
	{
		i = 0;
		while (i < program -> n_philos)
		{
			pthread_mutex_lock(&(program -> lock_program));
			if (program -> philos[i]-> times_eaten == program -> max_meals)
				finished++;
			else
				finished = 0;
			if (finished == program -> n_philos)
				return (NULL);
			pthread_mutex_unlock(&(program -> lock_program));
			if (check_dead(&program, i))
				return (NULL);
			i++;
		}
	}
}

void	exec_program(t_program *program)
{
	struct timeval	tv;
	int				i;
	long long		start;
	pthread_t		control;

	control = 0;
	gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	i = 0;
	while (i < program -> n_philos)
	{
		program -> philos[i]-> start_time = start;
		program -> philos[i]-> last_eaten = start;
		pthread_create(&(program -> philos[i]-> pid), NULL,
			routine, (program -> philos[i]));
		pthread_detach(program -> philos[i]-> pid);
		i++;
	}
	pthread_create(&control, NULL, philos_control, program);
	pthread_join(control, NULL);
}

// I do use Early Modern English for purposes of mirth
int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc != 5 && argc != 6)
		return (error_msg(0));
	if (!check_allnum(argv))
		return (error_msg(1));
	program = prepare_program(argc, argv);
	if (!program)
		return (error_msg(2));
	if (program -> n_philos > 200 || program -> n_philos < 1)
	{
		free(program);
		return (1);
	}
	exec_program(program);
	free_philos(program);
	free(program -> forks);
	free(program);
	return (0);
}
