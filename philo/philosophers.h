/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:59:49 by pjay              #+#    #+#             */
/*   Updated: 2023/02/15 16:03:25 by pjay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
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
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	int				is_dead;
	t_check			*ptr;
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
	pthread_mutex_t	*mutex_tab;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	check_mutex;
	pthread_mutex_t	check_mutex2;
	t_philo			*philo;

}	t_check;

long long int	current_time(void);
long long int	last_meal_was(t_philo *philo);
void			better_usleep(t_philo *philo, int time);
long long		time_since(t_check *mainthread);
int				fill_struct(char **av, t_check *mainthread);
int				init_philo(t_check *mainthread);
int				check_all(t_check *mainthread);
int				check_philo(t_philo *philo);
int				time_to_think(t_philo *philo, int test);
int				time_to_sleep(t_philo *philo);
int				forks_is_available(t_philo *philo);
int				ft_atoi(const char *nptr);
#endif
