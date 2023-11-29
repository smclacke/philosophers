/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 17:43:58 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/29 10:49:09 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * first philo's forks are swapped over to help avoid a deadlock
 * the rest have i as left fork and i - 1 for right fork
*/
int	assign_forks(t_god *info)
{
	int	i;
	int	count;

	i = 0;
	count = info->data->philo_count;
	while (i < count)
	{
		info->philipas[i].lfork_m = &info->data->forks_m[i];
		if (i == 0)
		{
			info->philipas[i].lfork_m = &info->data->forks_m[count - 1];
			info->philipas[i].rfork_m = &info->data->forks_m[i];
		}
		else
			info->philipas[i].rfork_m = &info->data->forks_m[i - 1];
		i++;
	}
	return (SUCCESS);
}

/**
 * lock the x_eat variable to check whether all philos have eaten enough 
 * in the monitor
*/
int	create_eat_amount_mutex(t_god *info)
{
	int		i;

	i = 0;
	while (i < info->data->philo_count)
	{
		if (pthread_mutex_init(&info->philipas[i].eat_xamount_m, NULL))
		{
			destroy_eat_amount_mutex(info, i);
			return (ft_error("eat_xamount mutex failed"));
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * lock the dinner_time variable to check whether someone
 * didn't eat in time and therefore died
*/
int	create_dinner_time_mutex(t_god *info)
{
	int		i;

	i = 0;
	while (i < info->data->philo_count)
	{
		if (pthread_mutex_init(&info->philipas[i].dinner_time_m, NULL))
		{
			destroy_eat_amount_mutex(info, i);
			destroy_dinner_time_mutex(info, i);
			return (ft_error("eat_time mutex failed"));
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * array of fork mutexes, each philo is then assigned a left and right fork
*/
int	create_forks_mutex(t_god *info)
{
	int					i;
	int					count;
	pthread_mutex_t		*forks;

	i = 0;
	count = info->data->philo_count;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * count);
	if (!forks)
	{
		ft_error("forks malloc");
		return (ERROR);
	}
	while (i < count)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			destroy_mutexes(forks, i);
			free(forks);
			return (ft_error("forks mutex init failed"));
		}
		i++;
	}
	info->data->forks_m = forks;
	return (SUCCESS);
}

/**
 * mutex array for the program: start, stop, display
 * all = 3, number of mutexes needed to control the general
 * run of the program
*/
int	create_prog_mutex(t_god *info)
{
	int				i;
	pthread_mutex_t	*prog;

	i = 0;
	prog = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ALL);
	if (!prog)
		return (ft_error("prog malloc failed"));
	while (i < ALL)
	{
		if (pthread_mutex_init(&prog[i], NULL) != 0)
		{
			destroy_mutexes(info->data->forks_m, i);
			destroy_mutexes(prog, i);
			free(prog);
			return (ft_error("prog mutex failed"));
		}
		i++;
	}
	info->data->prog_m = prog;
	return (SUCCESS);
}
