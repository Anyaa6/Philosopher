/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 13:48:27 by abonnel           #+#    #+#             */
/*   Updated: 2021/10/15 10:27:54 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args_are_numbers_only(char **argv)
{
	int				i;
	int				j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	save_args_in_struct(char **argv, t_arg *arg)
{
	int				i;
	long			arg_value;				

	i = 1;
	while (argv[i])
	{
		arg_value = ft_atoi(argv[i]);
		if (arg_value <= 0 || arg_value > 2147483647)
			return (1);
		if (i == 1)
			arg->nb_philo = (int)arg_value;
		else if (i == 2)
			arg->time_to_die = (int)arg_value;
		else if (i == 3)
			arg->time_eat = (int)arg_value;
		else if (i == 4)
			arg->time_sleep = (int)arg_value;
		else if (i == 5)
			arg->nb_meals = (int)arg_value;
		i++;
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_arg *arg)
{
	arg->argc = argc;
	if (check_args_are_numbers_only(argv))
		return (1);
	if (save_args_in_struct(argv, arg))
		return (1);
	if (argc == 5)
		arg->nb_meals = -1;
	return (0);
}
