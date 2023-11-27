/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutexes.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 17:43:58 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/27 19:59:14 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	create_eat_amount_mutex(t_god *info)
{
	int		i;

	i = 0;
	while (i < info->data->philo_count)
	{
		if (pthread_mutex_init(&info->philipas[i].eat_xamount_m, NULL))
		{
			destroy_eat_amount_mutex(info, i);
			return (ft_error("eat_xamount mutex failes"));
		}
		i++;
	}
	return (SUCCESS);
}

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
