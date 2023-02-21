/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:30:34 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 17:18:16 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	time_to_think(t_philo *philo, int test)
{
	if (check_philo(philo) == -1)
	{
		pthread_mutex_lock(&philo->ptr->write_mutex);
		printf("%lld %d is thinking\n", time_since(philo->ptr), philo->id);
		pthread_mutex_unlock(&philo->ptr->write_mutex);
		if (test != 0)
		{
			if (philo->ptr->n_of_philo % 2 == 0
				|| philo->ptr->t_to_die
				>= 2 * philo->ptr->t_to_eat + philo->ptr->t_to_sleep)
				better_usleep(philo,
					philo->ptr->t_to_eat - philo->ptr->t_to_sleep + 1);
			else
				better_usleep(philo, philo->ptr->t_to_die);
		}
	}
	else
		return (-1);
	return (0);
}

int	time_to_sleep(t_philo *philo)
{
	if (check_philo(philo) == -1)
	{
		pthread_mutex_lock(&philo->ptr->write_mutex);
		printf("%lld %d is sleeping\n", time_since(philo->ptr), philo->id);
		pthread_mutex_unlock(&philo->ptr->write_mutex);
	}
	else
		return (-1);
	better_usleep(philo, philo->ptr->t_to_sleep);
	return (0);
}

int	finish_forks(t_philo *philo)
{
	struct timeval	tv;

	if (check_philo(philo) == -1)
	{
		pthread_mutex_lock(&philo->ptr->write_mutex);
		printf("%lld %d has taken a fork\n", time_since(philo->ptr), philo->id);
		printf("%lld %d is eating\n", time_since(philo->ptr), philo->id);
		pthread_mutex_unlock(&philo->ptr->write_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->ptr->mutex_tab[philo->right_fork]);
		pthread_mutex_unlock(&philo->ptr->mutex_tab[philo->left_fork]);
		return (-1);
	}
	gettimeofday(&tv, NULL);
	pthread_mutex_lock(&philo->ptr->check_mutex2);
	philo->usec_last_meal = tv.tv_usec;
	philo->sec_last_meal = tv.tv_sec;
	philo->nb_meal++;
	pthread_mutex_unlock(&philo->ptr->check_mutex2);
	better_usleep(philo, philo->ptr->t_to_eat);
	return (0);
}

int	forks_is_available_2(t_philo *philo)
{
	if (philo->ptr->n_of_philo == 1)
	{
		better_usleep(philo, philo->ptr->t_to_die);
		printf("%lld %d is dead\n", time_since(philo->ptr), philo->id);
		pthread_mutex_unlock(&philo->ptr->mutex_tab[philo->left_fork]);
		return (-1);
	}
	if (check_philo(philo) == -1)
		pthread_mutex_lock(&philo->ptr->mutex_tab[philo->right_fork]);
	else
	{
		pthread_mutex_unlock(&philo->ptr->mutex_tab[philo->left_fork]);
		return (-1);
	}
	return (0);
}

int	forks_is_available(t_philo *philo)
{
	if (check_philo(philo) == -1)
		pthread_mutex_lock(&philo->ptr->mutex_tab[philo->left_fork]);
	else
		return (-1);
	if (check_philo(philo) == -1)
	{
		pthread_mutex_lock(&philo->ptr->write_mutex);
		printf("%lld %d has taken a fork\n", time_since(philo->ptr), philo->id);
		pthread_mutex_unlock(&philo->ptr->write_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philo->ptr->mutex_tab[philo->left_fork]);
		return (-1);
	}
	if (forks_is_available_2(philo) == -1 || finish_forks(philo) == -1)
		return (-1);
	pthread_mutex_unlock(&philo->ptr->mutex_tab[philo->right_fork]);
	pthread_mutex_unlock(&philo->ptr->mutex_tab[philo->left_fork]);
	return (0);
}
