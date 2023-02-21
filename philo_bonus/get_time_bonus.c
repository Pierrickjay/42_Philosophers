/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:05:26 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 17:17:52 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	result;

	result = 0;
	res = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			res *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * res);
}

long long int	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_since(t_check *mainthread)
{
	return (current_time()
		- (mainthread->sec_start * 1000 + mainthread->usec_start / 1000));
}

long long int	last_meal_was(t_philo *philo)
{
	if (!philo->sec_last_meal)
		return (0);
	return (current_time()
		- (philo->sec_last_meal * 1000 + philo->usec_last_meal / 1000));
}

void	better_usleep(t_philo *philo, int time, t_check *mainthread)
{
	long long int	i;

	i = time_since(mainthread);
	while (time_since(mainthread) < i + time
		&& ft_check(philo, mainthread) == -1)
		usleep(500);
}
