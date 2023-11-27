/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 16:18:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/26 18:50:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_god		info;

	if (argc != 5 && argc != 6)
	{
		ft_error_args(argc);
		return (ERROR);
	}
	if (init_input(&info, argc, argv) != SUCCESS)
		return (ERROR);
	if (create_philo_struct(&info) != SUCCESS)
		return (ERROR);
	if (life_cycle(&info) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
