/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 17:39:36 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/27 20:15:42 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * @brief	if the fifth arg was given and each philo must eat
 * 			a certain amount of times, this must be checked in 
 * 			the monitor so we know to stop when everyone 
 * 			has eaten enough
*/
static bool	eaten_enough(t_god *info)
{
	int		i;

	i = 0;
	while (i < info->data->philo_count)
	{
		pthread_mutex_lock(&info->philipas[i].eat_xamount_m);
		if (info->philipas[i].x_eaten < info->data->eat_arg_count)
		{
			pthread_mutex_unlock(&info->philipas[i].eat_xamount_m);
			return (false);
		}
		pthread_mutex_unlock(&info->philipas[i].eat_xamount_m);
		i++;
	}
	pthread_mutex_lock(&info->data->prog_m[STOP]);
	info->data->stop_b = true;
	pthread_mutex_unlock(&info->data->prog_m[STOP]);
	return (true);
}

/**
 * @brief	if too much time has passed since a philo last eat, 
 * 			they die and the simulation stops, this must be 
 * 			checked in the monitor during the prog run 
*/
static bool	died(t_god *info)
{
	int					i;
	uint64_t			last_eaten;
	uint64_t			time_gap;

	i = 0;
	last_eaten = 0;
	time_gap = 0;
	while (i < info->data->philo_count)
	{
		pthread_mutex_lock(&info->philipas[i].dinner_time_m);
		last_eaten = info->philipas[i].last_eaten_t;
		time_gap = current_time(info->data->start_time_t) - last_eaten;
		if (time_gap > (uint64_t)info->data->time_die)
		{
			display_message(&info->philipas[i], DIED);
			pthread_mutex_unlock(&info->philipas[i].dinner_time_m);
			return (true);
		}
		pthread_mutex_unlock(&info->philipas[i].dinner_time_m);
		i++;
	}
	return (false);
}

/**
 * @brief	check if the simulation can continue or not
 * 			two conditions for this: the philos had a certain
 * 			amount of times they needed to eat and have all 
 * 			eaten enough
 * 			OR
 * 			someone did not eat in time and died
*/
void	monitor(t_god *info)
{
	while (1)
	{
		if (died(info))
			return ;
		if (info->data->eat_arg_b && eaten_enough(info))
			return ;
		usleep (250);
	}
}
