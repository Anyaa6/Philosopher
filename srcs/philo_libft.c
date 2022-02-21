/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnel <abonnel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 13:14:23 by abonnel           #+#    #+#             */
/*   Updated: 2021/10/13 09:35:39 by abonnel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atoi(const char *str)
{
	int			i;
	long		neg;
	long		retour;

	neg = 1;
	retour = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		retour *= 10;
		retour += str[i] - 48;
		i++;
	}
	return (retour * neg);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_calloc(void **ptr, int size)
{
	*ptr = malloc(size);
	if (*ptr == NULL)
		return (1);
	memset(*ptr, 0, size);
	return (0);
}

void	free_set_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}
