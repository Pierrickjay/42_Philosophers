/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:28:02 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 12:04:55 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine_philo(void *args)
{
	t_philo	*philo;
	int		a;

	a = 0;
	philo = (t_philo *)args;
	if (philo->id % 2 != 0)
		usleep(500);
	while (check_philo(philo) == -1)
	{
		if (time_to_think(philo, a) == -1)
			return (philo);
		a++;
		if (forks_is_available(philo) == -1)
			return (philo);
		if (time_to_sleep(philo) == -1)
			return (philo);
	}
	return (philo);
}

int	init_philo(t_check *mainthread)
{
	int	i;

	i = -1;
	while (++i < mainthread->n_of_philo)
		if (pthread_mutex_init(&mainthread->mutex_tab[i], NULL) != 0)
			return (0);
	if (pthread_mutex_init(&mainthread->write_mutex, NULL) != 0
		|| pthread_mutex_init(&mainthread->check_mutex, NULL) != 0
		|| pthread_mutex_init(&mainthread->check_mutex2, NULL) != 0)
		return (0);
	i = -1;
	while (++i < mainthread->n_of_philo)
	{
		if (pthread_create(&mainthread->philo[i].thread, NULL,
				routine_philo, (void *)&mainthread->philo[i]) != 0)
			return (0);
	}
	return (1);
}
