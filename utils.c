/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexigar <alexigar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:26:03 by alexigar          #+#    #+#             */
/*   Updated: 2024/09/20 13:14:02 by alexigar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_allnum(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
		j = 0;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	cont;

	cont = 0;
	while (*str >= '0' && *str <= '9')
	{
		cont = cont * 10 + (*str - '0');
		str++;
	}
	return (cont);
}

void	*free_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program -> n_philos)
	{
		free(program -> philos[i]);
		i++;
	}
	free(program -> philos);
	return (NULL);
}

int	error_msg(int errno)
{
	if (errno == 0)
		printf("Thou hast introduced an incorrect number of arguments\n");
	else if (errno == 1)
		printf("Thou needest positive numeric arguments\n");
	else if (errno == 2)
		printf("There was a problem of remembrance\n");
	return (1);
}

t_program	*error_msg2(t_program *program)
{
	printf("Thou hast an invalid number of philosophers\n");
	return (program);
}
