/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 10:11:01 by abonnel           #+#    #+#             */
/*   Updated: 2021/10/15 10:32:45 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	destroy_mutexes(t_philo **philo, t_arg *arg)
{
	int			i;

	i = 0;
	while (i < arg->nb_philo)
	{
		if (arg->fork_id)
			pthread_mutex_destroy(&arg->fork_id[i]);
		if (*philo)
			pthread_mutex_destroy(&(*philo)[i].eat_mutex);
		i++;
	}
	if (*philo)
		pthread_mutex_destroy(&arg->speech_mutex);
}

void	print_error_msg(int error)
{
	if (error == SYSCALL_ERR)
		printf("Syscall error");
	else if (error == ARG_ERR)
		printf("Issue with arguments");
	else if (error == INITIALIZATION)
		printf("Issue while initializing mutexes / threads");
	printf("\n");
}

void	free_display_error(t_philo **philo, t_arg *arg, int error)
{
	if (error)
		print_error_msg(error);
	destroy_mutexes(philo, arg);
	if (*philo)
		free_set_null((void **)philo);
	if (arg->fork_id)
		free_set_null((void **)&arg->fork_id);
}
