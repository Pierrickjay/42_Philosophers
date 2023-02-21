/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:12:39 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 15:55:26 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# define TRUE 1
# define FALSE 0
# define OPEN 1
# define CLOSE 0

typedef struct s_check	t_check;

typedef struct s_philo
{
	int				id;
	long int		usec_last_meal;
	long			sec_last_meal;
	int				nb_meal;
	pthread_t		thread;
	int				is_dead;
}	t_philo;

typedef struct s_check
{
	int				n_of_philo;
	int				n_of_forks;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				meal_to_eat;
	int				nb_meal;
	long int		sec_start;
	long int		usec_start;
	int				exit;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_eat;
	sem_t			*sem_test;
}	t_check;

void			fill_struct(char **av, t_check *mainthread);
void			fill_philo(t_philo *philo, int i);
int				init_philo_forks(t_check *mainthread);
int				forks_is_available(t_philo *philo, t_check *mainthread);
int				time_to_sleep(t_philo *philo, t_check *mainthread);
int				time_to_think(t_philo *philo, t_check *mainthread, int test);
void			better_usleep(t_philo *philo, int time, t_check *mainthread);
long long		time_since(t_check *mainthread);
long long int	last_meal_was(t_philo *philo);
int				ft_check(t_philo *philo, t_check *mainthread);
int				ft_atoi(const char *nptr);

#endif
