/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:43:23 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 17:17:43 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_close_my_sem(t_check *mainthread)
{
	sem_close(mainthread->sem_forks);
	sem_close(mainthread->sem_write);
	sem_close(mainthread->sem_test);
}

int	ft_check(t_philo *philo, t_check *mainthread)
{
	int	i;

	i = -1;
	if (mainthread->nb_meal == TRUE
		&& philo->nb_meal >= mainthread->meal_to_eat)
	{
		sem_post(mainthread->sem_eat);
		mainthread->nb_meal = FALSE;
		return (-1);
	}
	else if (last_meal_was(philo) > mainthread->t_to_die)
	{
		sem_wait(mainthread->sem_write);
		printf("%lld %d died\n", time_since(mainthread), philo->id);
		ft_close_my_sem(mainthread);
		while (++i < mainthread->n_of_philo)
			sem_post(mainthread->sem_eat);
		exit (0);
	}
	else
		return (-1);
}
