/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 15:54:57 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 16:27:16 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo_2(t_philo *philo)
{
	int	compteur;
	int	i;

	i = 0;
	compteur = 0;
	if (philo->ptr->nb_meal == TRUE)
	{
		while (i < philo->ptr->n_of_philo)
		{
			if (philo->ptr->philo[i].nb_meal < philo->ptr->meal_to_eat)
				compteur++;
			i++;
		}
		if (compteur == 0)
		{
			philo->is_dead = TRUE;
			philo->ptr->exit = TRUE;
			pthread_mutex_unlock(&philo->ptr->check_mutex2);
			return (1);
		}
	}
	return (0);
}

int	check_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->ptr->check_mutex2);
	if (philo->is_dead != TRUE && philo->ptr->exit != TRUE
		&& last_meal_was(philo) > philo->ptr->t_to_die)
	{
		philo->is_dead = TRUE;
		philo->ptr->exit = TRUE;
		pthread_mutex_lock(&philo->ptr->write_mutex);
		printf("%lld %d died\n", time_since(philo->ptr), philo->id);
		pthread_mutex_unlock(&philo->ptr->write_mutex);
		pthread_mutex_unlock(&philo->ptr->check_mutex2);
		return (1);
	}
	if (check_philo_2(philo) == 1)
		return (1);
	if (philo->ptr->exit == TRUE)
	{
		pthread_mutex_unlock(&philo->ptr->check_mutex2);
		return (1);
	}
	pthread_mutex_unlock(&philo->ptr->check_mutex2);
	return (-1);
}
