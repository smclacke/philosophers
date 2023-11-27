/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   destroy_mutexes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 17:48:13 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/22 18:31:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	destroy_eat_amount_mutex(t_god *info, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&info->philipas[i].eat_xamount_m);
		i++;
	}
}

void	destroy_dinner_time_mutex(t_god *info, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&info->philipas[i].dinner_time_m);
		i++;
	}
}

void	destroy_mutexes(pthread_mutex_t *mutex, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
}

void	destroy_everything(t_god *info)
{
	int		amount_philos;

	amount_philos = info->data->philo_count;
	destroy_mutexes(info->data->forks_m, amount_philos);
	destroy_mutexes(info->data->prog_m, ALL);
	destroy_eat_amount_mutex(info, amount_philos);
	destroy_dinner_time_mutex(info, amount_philos);
	free(info->philipas);
	free(info->data->forks_m);
	free(info->data->prog_m);
	free(info->data);
}
