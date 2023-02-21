/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:30:34 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 17:13:25 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	time_to_think(t_philo *philo, t_check *mainthread, int test)
{
	if (ft_check(philo, mainthread) == -1)
	{
		sem_wait(mainthread->sem_write);
		printf("%lld %d is thinking\n", time_since(mainthread), philo->id);
		sem_post(mainthread->sem_write);
		if (test != 0)
		{
			if (mainthread->n_of_philo % 2 == 0
				|| mainthread->t_to_die
				>= 2 * mainthread->t_to_eat + mainthread->t_to_sleep)
				better_usleep(philo,
					mainthread->t_to_eat - mainthread->t_to_sleep + 1,
					mainthread);
			else
				better_usleep(philo, mainthread->t_to_die, mainthread);
		}
	}
	else
		return (-1);
	return (0);
}

int	time_to_sleep(t_philo *philo, t_check *mainthread)
{
	if (ft_check(philo, mainthread) == -1)
	{
		sem_wait(mainthread->sem_write);
		printf("%lld %d is sleeping\n", time_since(mainthread), philo->id);
		sem_post(mainthread->sem_write);
	}
	else
		return (-1);
	better_usleep(philo, mainthread->t_to_sleep, mainthread);
	return (0);
}

void	deal_w_one(t_philo *philo, t_check *mainthread)
{
	better_usleep(philo, mainthread->t_to_die, mainthread);
	sem_wait(mainthread->sem_write);
	printf("%lld %d died\n", time_since(mainthread), philo->id);
	sem_post(mainthread->sem_write);
	sem_post(mainthread->sem_eat);
}

int	finish_forks(t_philo *philo, t_check *mainthread)
{
	struct timeval	tv;

	if (mainthread->n_of_philo == 1)
		deal_w_one(philo, mainthread);
	if (ft_check(philo, mainthread) == -1)
	{
		sem_wait(mainthread->sem_forks);
		sem_wait(mainthread->sem_write);
		printf("%lld %d has taken a fork\n", time_since(mainthread), philo->id);
		printf("%lld %d is eating\n", time_since(mainthread), philo->id);
		sem_post(mainthread->sem_write);
		gettimeofday(&tv, NULL);
		philo->usec_last_meal = tv.tv_usec;
		philo->sec_last_meal = tv.tv_sec;
		better_usleep(philo, mainthread->t_to_eat, mainthread);
		philo->nb_meal++;
		return (0);
	}
	else
		return (-1);
}

int	forks_is_available(t_philo *philo, t_check *mainthread)
{
	if (ft_check(philo, mainthread) == -1)
	{
		sem_wait(mainthread->sem_forks);
		sem_wait(mainthread->sem_write);
		printf("%lld %d has taken a fork\n", time_since(mainthread), philo->id);
		sem_post(mainthread->sem_write);
	}
	if (finish_forks(philo, mainthread) == -1)
		return (-1);
	sem_post(mainthread->sem_forks);
	sem_post(mainthread->sem_forks);
	return (0);
}
