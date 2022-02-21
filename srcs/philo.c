/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:57:21 by abonnel           #+#    #+#             */
/*   Updated: 2021/10/15 10:26:02 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initialize_structs(t_philo **philo, t_arg *arg)
{
	*philo = NULL;
	arg->fork_id = NULL;
	arg->no_dead_philo = 1;
	arg->begin_t = 0;
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_arg			arg;

	initialize_structs(&philo, &arg);
	if ((argc != 5 && argc != 6) || parse_arguments(argc, argv, &arg))
	{
		free_display_error(&philo, &arg, ARG_ERR);
		return (ARG_ERR);
	}
	if (create_philo_and_mutexes(&philo, &arg) || launch_philos(philo, &arg))
	{
		free_display_error(&philo, &arg, INITIALIZATION);
		return (INITIALIZATION);
	}
	accurate_sleep(arg.time_to_die);
	while (simulation_continues(philo, &arg))
		;
	wait_for_threads_to_end(philo, &arg);
	free_display_error(&philo, &arg, NO_ERROR);
}
