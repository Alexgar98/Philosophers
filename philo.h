/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:09:59 by alexigar          #+#    #+#             */
/*   Updated: 2024/09/20 13:18:58 by alexigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philosopher	t_philosopher;
typedef struct s_program		t_program;

typedef struct s_philosopher
{
	int				id; //Philosopher ID (1, 2, ...)
	pthread_t		pid; //Thread ID. To change if needed
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
	int				times_eaten;
	long long		last_eaten; //Last timestamp when philosopher has eaten
	int				dead; //0 alive, 1 dead
	int				is_eating;
	int				forks_held;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock_times_eaten;
	pthread_mutex_t	lock_eating;
	long long		start_time;
	t_program		*program;
}	t_philosopher;

typedef struct s_program
{
	int				n_philos;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				max_meals;
	int				dead;
	pthread_mutex_t	*forks;
	t_philosopher	**philos;
	pthread_mutex_t	lock_program;
	pthread_mutex_t	lock_dead;
}	t_program;

void			take_fork(t_philosopher *philo, pthread_mutex_t *fork);
void			p_eat(t_philosopher *philo);
void			p_sleep(t_philosopher *philo);
void			p_think(t_philosopher *philo);
void			p_die(t_philosopher *philo);
pthread_mutex_t	*init_forks(t_program *program);
void			destroy_forks(pthread_mutex_t *forks);
void			kill_all(t_program *program);
void			*free_philos(t_program *program);
int				ft_atoi(const char *str);
int				check_allnum(char **argv);
t_program		*prepare_program(int argc, char **argv);
t_program		*init_program(int argc, char **argv);
t_philosopher	**init_philos(t_program *program);
t_philosopher	*init_philo(t_program *program, int i);
void			destroy_mutex(t_philosopher *philo);
int				error_msg(int errno);
int				check_death(t_philosopher *philo);
t_program		*error_msg2(t_program *program);
void			unlock_forks(t_philosopher *philo);

#endif
