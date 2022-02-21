/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:11:54 by abonnel           #+#    #+#             */
/*   Updated: 2021/10/15 10:19:35 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	display_status(long timestamp, int status, t_philo *philo)
{
	if (status == DROPING_FORK)
		return (STOP);
	pthread_mutex_lock(&philo->arg->speech_mutex);
	if (philo->arg->no_dead_philo == 0)
	{
		pthread_mutex_unlock(&philo->arg->speech_mutex);
		return (STOP);
	}
	if (status == EATING)
		printf("%ld philo %d is eating\n", timestamp, philo->id);
	else if (status == SLEEPING)
		printf("%ld philo %d is sleeping\n", timestamp, philo->id);
	else if (status == TAKING_FORK)
		printf("%ld philo %d has taken a fork\n", timestamp, philo->id);
	else if (status == THINKING)
		printf("%ld philo %d is thinking\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->arg->speech_mutex);
	return (CONTINUE);
}

void	philo_starts(int status, t_philo *philo, t_arg *arg)
{
	long				timestamp;

	timestamp = time_is();
	if (display_status(timestamp - arg->begin_t, status, philo) == STOP)
		return ;
	if (status == SLEEPING)
		accurate_sleep(arg->time_sleep);
	else if (status == EATING)
	{
		philo->lastmeal_t = timestamp;
		philo->meals_eaten++;
		accurate_sleep(arg->time_eat);
	}
}

void	set_right_fork(pthread_mutex_t **right, t_philo *philo, t_arg *arg)
{
	if (philo->id == arg->nb_philo)
		*right = &arg->fork_id[0];
	else
		*right = &arg->fork_id[philo->id];
}

void	philo_is(int status, pthread_mutex_t *right, \
	int (*mutex)(pthread_mutex_t *), t_philo *philo)
{
	(*mutex)(&philo->arg->fork_id[philo->id - 1]);
	philo_starts(status, philo, philo->arg);
	(*mutex)(right);
	philo_starts(status, philo, philo->arg);
}

void	*philo_live(void *given_arg)
{
	t_philo				*philo;
	pthread_mutex_t		*right;

	philo = (t_philo *)given_arg;
	set_right_fork(&right, philo, philo->arg);
	while (philo->arg->begin_t == 0)
		;
	if (philo->id % 2 == 0 && philo->arg->nb_philo < 100)
	{
		philo_starts(SLEEPING, philo, philo->arg);
		philo_starts(THINKING, philo, philo->arg);
	}
	while (philo->arg->no_dead_philo)
	{
		philo_is(TAKING_FORK, right, &pthread_mutex_lock, philo);
		pthread_mutex_lock(&philo->eat_mutex);
		philo_starts(EATING, philo, philo->arg);
		pthread_mutex_unlock(&philo->eat_mutex);
		philo_is(DROPING_FORK, right, &pthread_mutex_unlock, philo);
		philo_starts(SLEEPING, philo, philo->arg);
		philo_starts(THINKING, philo, philo->arg);
	}
	return (NULL);
}
