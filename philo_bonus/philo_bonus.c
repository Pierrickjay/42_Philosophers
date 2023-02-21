/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:28:02 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 12:29:47 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	routine_philo(t_check *mainthread, int i)
{
	t_philo	philo;
	int		a;

	a = 0;
	sem_wait(mainthread->sem_test);
	if (i % 2 != 0)
		usleep(500);
	fill_philo(&philo, i);
	while (1)
	{
		if (time_to_think(&philo, mainthread, a) == -1)
			return ;
		a++;
		if (forks_is_available(&philo, mainthread) == -1)
			return ;
		if (time_to_sleep(&philo, mainthread) == -1)
			return ;
	}
	return ;
}

int	close_all(t_check *mainthread)
{
	sem_close(mainthread->sem_forks);
	sem_close(mainthread->sem_write);
	sem_close(mainthread->sem_eat);
	sem_close(mainthread->sem_test);
	return (0);
}

int	init_philo_forks(t_check *mainthread)
{
	int		i;
	pid_t	pids[2000];

	i = -1;
	while (++i < mainthread->n_of_philo)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			routine_philo(mainthread, i);
			break ;
		}
	}
	i = -1;
	while (++i < mainthread->n_of_philo)
		sem_post(mainthread->sem_test);
	i = -1;
	while (++i < mainthread->n_of_philo)
		sem_wait(mainthread->sem_eat);
	i = -1;
	while (++i < mainthread->n_of_philo)
		kill(pids[i], SIGKILL);
	return (close_all(mainthread));
}
