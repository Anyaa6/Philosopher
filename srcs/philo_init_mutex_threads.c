/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_mutex_threads.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:41:24 by abonnel           #+#    #+#             */
/*   Updated: 2021/10/15 10:16:46 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_fork_and_eat_mutex(t_philo **philo, t_arg *arg)
{
	int			i;

	if (pthread_mutex_init(&arg->speech_mutex, NULL))
		return (MUTEX_INIT);
	i = 0;
	while (i < arg->nb_philo)
	{
		if (pthread_mutex_init(&arg->fork_id[i], NULL))
			return (MUTEX_INIT);
		if (pthread_mutex_init(&(*philo)[i].eat_mutex, NULL))
			return (MUTEX_INIT);
		i++;
	}
	return (NO_ERROR);
}

void	init_philos_values(t_philo *philo, t_arg *arg)
{
	int			i;

	i = 0;
	while (i < arg->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].lastmeal_t = 0;
		philo[i].arg = arg;
		i++;
	}
}

int	create_philo_and_mutexes(t_philo **philo, t_arg *arg)
{
	if (ft_calloc((void **)philo, sizeof(t_philo) * arg->nb_philo))
		return (CREA_PHILO);
	if (ft_calloc((void **)&arg->fork_id, sizeof(pthread_mutex_t) * \
		arg->nb_philo))
		return (CREA_FORK);
	if (init_fork_and_eat_mutex(philo, arg))
		return (MUTEX_INIT);
	init_philos_values(*philo, arg);
	return (NO_ERROR);
}

int	launch_philos(t_philo *philo, t_arg *arg)
{
	int			i;

	i = 0;
	while (i < arg->nb_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &philo_live, &philo[i]))
			return (THREAD_INIT);
		i++;
	}
	arg->begin_t = time_is();
	return (NO_ERROR);
}
