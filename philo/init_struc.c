/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:00:26 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 16:05:34 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fill_philo(t_check *mainthread)
{
	int	number;

	number = 0;
	while (number != mainthread->n_of_philo)
	{
		mainthread->philo[number].id = number;
		mainthread->philo[number].nb_meal = 0;
		mainthread->philo[number].ptr = mainthread;
		mainthread->philo[number].sec_last_meal = 0;
		mainthread->philo[number].usec_last_meal = 0;
		mainthread->philo[number].is_dead = FALSE;
		if (number != mainthread->n_of_philo - 1)
		{
			mainthread->philo[number].left_fork = number;
			mainthread->philo[number].right_fork = number + 1;
		}
		else
		{
			mainthread->philo[number].right_fork = number;
			mainthread->philo[number].left_fork = 0;
		}
		number++;
	}
}

void	fill_mainthread(char **av, t_check *mainthread)
{
	struct timeval	tv;

	mainthread->n_of_philo = ft_atoi(av[1]);
	mainthread->n_of_forks = ft_atoi(av[1]);
	mainthread->t_to_die = ft_atoi(av[2]);
	mainthread->t_to_eat = ft_atoi(av[3]);
	mainthread->t_to_sleep = ft_atoi(av[4]);
	mainthread->exit = FALSE;
	if (av[5])
	{
		mainthread->meal_to_eat = ft_atoi(av[5]);
		mainthread->nb_meal = TRUE;
	}
	else
		mainthread->nb_meal = FALSE;
	gettimeofday(&tv, NULL);
	mainthread->sec_start = tv.tv_sec;
	mainthread->usec_start = tv.tv_usec;
}

int	fill_struct(char **av, t_check *mainthread)
{
	fill_mainthread(av, mainthread);
	mainthread->philo = malloc(sizeof(t_philo) * mainthread->n_of_philo);
	if (!mainthread->philo)
		return (-1);
	mainthread->mutex_tab
		= malloc(sizeof(pthread_mutex_t) * (mainthread->n_of_philo + 2));
	if (!mainthread->mutex_tab)
	{
		free(mainthread->philo);
		return (-1);
	}
	fill_philo(mainthread);
	return (0);
}
