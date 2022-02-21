/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:57:35 by abonnel           #+#    #+#             */
/*   Updated: 2021/10/15 10:12:00 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct timeval	t_timeval;

typedef struct s_arg
{
	int				argc;
	int				no_dead_philo;
	int				nb_philo;
	int				time_to_die;
	int				time_sleep;
	int				time_eat;
	int				nb_meals;
	long int		begin_t;
	pthread_mutex_t	*fork_id;
	pthread_mutex_t	speech_mutex;
}		t_arg;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	long int		lastmeal_t;
	pthread_mutex_t	eat_mutex;
	t_arg			*arg;
}	t_philo;

enum			e_errors
{
	SYSCALL_ERR = -1,
	NO_ERROR = 0,
	ARG_ERR = 1,
	INITIALIZATION = 2,
	CREA_PHILO = 3,
	CREA_FORK = 4,
	MUTEX_INIT = 5,
	THREAD_INIT = 6
};

enum			e_status
{
	DROPING_FORK = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	TAKING_FORK = 4,
	DYING = 5,
	ATE_ENOUGH = 6
};

enum			e_display_exit_status
{
	STOP = 1,
	CONTINUE = 2,
};

//****************
//philo_libft.c
//****************
long		ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_calloc(void **ptr, int size);
void		free_set_null(void **ptr);

//****************
//philo_parsing.c
//****************
int			parse_arguments(int argc, char **argv, t_arg *arg);

//****************
//philo_exit_and_free.c
//****************
void		free_display_error(t_philo **philo, t_arg *arg, int error);

//****************
//philo_init_mutex_threads.c
//****************
int			create_philo_and_mutexes(t_philo **philo, t_arg *arg);
int			launch_philos(t_philo *philo, t_arg *arg);

//****************
//philo_live.c
//****************
void		*philo_live(void *given_arg);

//****************
//philo_time.c
//****************
long		time_is(void);
void		accurate_sleep(long ms);

//****************
//philo_stop_simulation.c
//****************
int			simulation_continues(t_philo *philo, t_arg *arg);
void		wait_for_threads_to_end(t_philo *philo, t_arg *arg);

#endif
