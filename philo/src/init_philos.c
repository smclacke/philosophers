/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_philos.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 17:43:30 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/27 14:37:47 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_philo_mutexes(t_god *info)
{
	if (create_eat_amount_mutex(info))
		return (ft_error("eat amount mutex failed"));
	if (create_dinner_time_mutex(info))
		return (ft_error("eat time mutex failed"));
	if (assign_forks(info))
		return (ft_error("assigning forks failed"));
	return (SUCCESS);
}

static t_philo	*init_philos(t_god *info, t_philo *philo_arr)
{
	int			i;
	t_philo		one_philo;

	i = 0;
	if (info->data->philo_count == 1)
		one_philo.one_philo_b = true;
	else
		one_philo.one_philo_b = false;
	while (i < info->data->philo_count)
	{
		one_philo.id = i + 1;
		one_philo.data = info->data;
		one_philo.last_eaten_t = 0;
		one_philo.x_eaten = 0;
		philo_arr[i] = one_philo;
		i++;
	}
	return (philo_arr);
}

int	create_philo_struct(t_god *info)
{
	t_philo		*philo_arr;

	philo_arr = malloc(sizeof(t_philo) * info->data->philo_count);
	if (philo_arr == NULL)
	{
		free(info);
		return (ft_error("philo_arr malloc failed"));
	}
	philo_arr = init_philos(info, philo_arr);
	if (!philo_arr)
	{
		free(info);
		return (ft_error("init philos failed"));
	}
	info->philipas = philo_arr;
	if (init_philo_mutexes(info))
	{
		free(info);
		return (ERROR);
	}
	return (SUCCESS);
}
