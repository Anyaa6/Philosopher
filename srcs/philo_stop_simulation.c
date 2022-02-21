/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stop_simulation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:58:03 by abonnel           #+#    #+#             */
/*   Updated: 2021/10/15 10:13:58 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	stop_simulation(int reason, long timestamp, t_philo *philo, t_arg *arg)
{
	if (reason == DYING)
		pthread_mutex_lock(&philo->eat_mutex);
	pthread_mutex_lock(&arg->speech_mutex);
	if (reason == DYING)
		printf("%ld philo %d died\n", timestamp, philo->id);
	else
		printf("All philos ate enough, yum!\n");
	arg->no_dead_philo = 0;
	if (arg->nb_philo == 1)
		pthread_mutex_unlock(&arg->fork_id[0]);
	pthread_mutex_unlock(&arg->speech_mutex);
	if (reason == DYING)
		pthread_mutex_unlock(&philo->eat_mutex);
}

int	simulation_continues(t_philo *philo, t_arg *arg)
{
	long			current_time;
	int				i;
	int				nb_of_philos_ate_enough;

	i = 0;
	nb_of_philos_ate_enough = 0;
	current_time = time_is();
	while (i < arg->nb_philo)
	{
		if (current_time - philo[i].lastmeal_t >= arg->time_to_die)
		{
			stop_simulation(DYING, current_time - arg->begin_t, &philo[i], arg);
			return (0);
		}
		if (philo[i].meals_eaten >= arg->nb_meals)
			nb_of_philos_ate_enough++;
		i++;
	}
	if (nb_of_philos_ate_enough == arg->nb_philo && arg->nb_meals > 0)
	{
		stop_simulation(ATE_ENOUGH, 0, NULL, arg);
		return (0);
	}
	return (1);
}

void	wait_for_threads_to_end(t_philo *philo, t_arg *arg)
{
	int				i;

	i = 0;
	while (i < arg->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}
