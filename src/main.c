/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 16:18:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/21 22:21:29 by SarahLouise   ########   odam.nl         */
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
