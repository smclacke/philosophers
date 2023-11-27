/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 16:36:39 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/27 20:03:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_data_mutexes(t_god *info)
{
	if (create_forks_mutex(info))
		return (ft_error("data->forks mutex noped"));
	if (create_prog_mutex(info))
		return (ft_error("data->prog mutex failed"));
	return (SUCCESS);
}

static int	check_arg_vals(t_god *info)
{
	if (info->data->philo_count <= 0 || info->data->time_die <= 0)
		return (ft_error(WRONG_ARGS));
	if (info->data->time_eat <= 0 || info->data->time_sleep <= 0)
		return (ft_error(WRONG_ARGS));
	if (info->data->eat_arg_b && info->data->eat_arg_count <= 0)
		return (ft_error(WRONG_ARGS));
	return (SUCCESS);
}

static int	init_data(t_god *info, int argc, char **argv)
{
	info->data->philo_count = ft_atoi(argv[1]);
	info->data->time_die = ft_atoi(argv[2]);
	info->data->time_eat = ft_atoi(argv[3]);
	info->data->time_sleep = ft_atoi(argv[4]);
	if (argc == 5)
	{
		info->data->eat_arg_b = false;
		info->data->eat_arg_count = 0;
	}
	else if (argc == 6)
	{
		info->data->eat_arg_b = true;
		info->data->eat_arg_count = ft_atoi(argv[5]);
	}
	info->data->start_time_t = 0;
	info->data->stop_b = false;
	info->data->died_b = false;
	info->data->yes_start_b = false;
	if (check_arg_vals(info))
		return (ERROR);
	return (SUCCESS);
}

int	init_input(t_god *info, int argc, char **argv)
{
	info->data = (t_data *)malloc(sizeof(t_data));
	if (!info->data)
		return (ft_error("data malloc failed"));
	if (init_data(info, argc, argv))
	{
		free(info->data);
		return (ERROR);
	}
	if (init_data_mutexes(info))
	{
		free(info->data);
		return (ERROR);
	}
	return (SUCCESS);
}
