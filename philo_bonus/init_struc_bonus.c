/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:00:26 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 09:19:35 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
	Si on cree un semaphore dead que on l'init a 1
*/

void	fill_philo(t_philo *philo, int i)
{
		philo->id = i;
		philo->nb_meal = 0;
		philo->sec_last_meal = 0;
		philo->usec_last_meal = 0;
		philo->is_dead = FALSE;
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

void	fill_struct(char **av, t_check *mainthread)
{
	sem_unlink("/sem_forks");
	sem_unlink("/sem_write");
	sem_unlink("/sem_eat");
	sem_unlink("/sem_test");
	fill_mainthread(av, mainthread);
	mainthread->sem_forks
		= sem_open
		("/sem_forks", O_CREAT, S_IRUSR | S_IWUSR, mainthread->n_of_philo);
	mainthread->sem_write
		= sem_open
		("/sem_write", O_CREAT, S_IRUSR | S_IWUSR, 1);
	mainthread->sem_test
		= sem_open
		("/sem_test", O_CREAT, S_IRUSR | S_IWUSR, 0);
	mainthread->sem_eat
		= sem_open
		("/sem_eat", O_CREAT, S_IRUSR | S_IWUSR, 0);
	if (mainthread->sem_eat == SEM_FAILED || mainthread->sem_test == SEM_FAILED)
		exit (0);
	if (mainthread->sem_forks == SEM_FAILED
		|| mainthread->sem_write == SEM_FAILED)
		exit (0);
}
