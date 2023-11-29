/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   life_cycle.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 17:29:41 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/29 10:59:57 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	join(pthread_t *threads, int count)
{
	int		i;

	i = 0;
	while (i < count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

/**
 * only if all philo threads have been successfully created,
 * can we set our start bool to true and being the simulation
*/
static int	create_threads(t_god *info, pthread_t *threads)
{
	int		i;

	i = 0;
	pthread_mutex_lock(&info->data->prog_m[START]);
	while (i < info->data->philo_count)
	{
		if (pthread_create(&threads[i], NULL, &routine, &info->philipas[i]))
		{
			pthread_mutex_unlock(&info->data->prog_m[START]);
			join(threads, i);
			return (ERROR);
		}
		i++;
	}
	info->data->yes_start_b = true;
	info->data->start_time_t = ft_get_time();
	pthread_mutex_unlock(&info->data->prog_m[START]);
	return (SUCCESS);
}

static int	thread_and_monitor(t_god *info, pthread_t *threads)
{
	if (create_threads(info, threads))
	{
		free(threads);
		destroy_everything(info);
		return (ft_error("couldn't create philo threads"));
	}
	monitor(info);
	join(threads, info->data->philo_count);
	free(threads);
	destroy_everything(info);
	return (SUCCESS);
}

/**
 * one philo has a slightly didn't life routine,
 * so it's handled separately from the rest
*/
int	life_cycle(t_god *info)
{
	pthread_t	*threads;

	threads = malloc(info->data->philo_count * sizeof(pthread_t));
	if (threads == NULL)
	{
		destroy_everything(info);
		return (ft_error("thread malloc noped"));
	}
	if (info->philipas->one_philo_b == true)
	{
		if (handle_one(info, threads))
			return (ERROR);
		return (SUCCESS);
	}
	if (thread_and_monitor(info, threads))
		return (ft_error("threading fail"));
	return (SUCCESS);
}
