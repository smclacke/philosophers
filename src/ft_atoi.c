/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 12:51:09 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/27 14:37:13 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

int	ft_atoi(char *str)
{
	long	neg;
	long	num;
	long	i;

	i = 0;
	neg = 1;
	num = 0;
	while ((ft_isspace(str[i])))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - 48);
		if ((num * neg) > INT_MAX || (num * neg) < INT_MIN)
			ft_error("atoi error");
		i++;
	}
	return (num * neg);
}
