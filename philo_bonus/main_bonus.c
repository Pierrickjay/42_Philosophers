/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:39:01 by pjay              #+#    #+#             */
/*   Updated: 2023/02/17 14:54:33 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

void	check_args(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	if (ft_atoi(av[1]) <= 0)
	{
		printf("Error\n");
		exit (0);
	}
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("Error\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

/* Faire des forks pour le nombre de philo
*/

int	main(int ac, char **av)
{
	t_check	mainthread;
	int		i;

	i = -1;
	if (!av[1] || ac <= 4)
		return (0);
	check_args(av, ac);
	fill_struct(av, &mainthread);
	init_philo_forks(&mainthread);
	sem_close(mainthread.sem_forks);
}
