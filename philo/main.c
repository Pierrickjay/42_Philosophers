/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:15:40 by pjay              #+#    #+#             */
/*   Updated: 2023/02/17 13:50:28 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	if (ft_atoi(av[1]) <= 0)
	{
		printf("Error\n");
		return (-1);
	}
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
			{
				printf("Error\n");
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	free_all(t_check *mainthread)
{
	int	i;

	i = -1;
	while (++i < mainthread->n_of_philo)
		pthread_join(mainthread->philo[i].thread, NULL);
	free(mainthread->philo);
	free(mainthread->mutex_tab);
}

int	main(int ac, char **av)
{
	t_check	mainthread;

	if (!av[1] || ac <= 4)
		return (0);
	if (check_args(av, ac) == -1)
		return (0);
	if (fill_struct(av, &mainthread) == -1)
		return (0);
	if (!init_philo(&mainthread))
		return (0);
	free_all(&mainthread);
}
