/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 16:34:48 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/27 14:38:56 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error_args(int argc)
{
	if (argc < 5)
		printf("Too few arguments\n");
	else if (argc > 6)
		printf("Too many arguments\n");
}

int	ft_error(char *str)
{
	printf("Error: %s\n", str);
	return (ERROR);
}
