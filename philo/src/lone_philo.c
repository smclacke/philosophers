/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lone_philo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/26 19:40:19 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/27 15:43:12 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->data->prog_m[START]);
	pthread_mutex_unlock(&philo->data->prog_m[START]);
	display_message(philo, THINKING);
	pthread_mutex_lock(philo->lfork_m);
	display_message(philo, TAKEN_FORK);
	pthread_mutex_unlock(philo->lfork_m);
	ft_sleep(philo, philo->data->time_eat);
	return (NULL);
}

static	int	create_one_philo(t_god *info, pthread_t *threads)
{
	pthread_mutex_lock(&info->data->prog_m[START]);
	if (pthread_create(&threads[0], NULL, &one_philo, &info->philipas[0]))
	{
		pthread_mutex_unlock(&info->data->prog_m[START]);
		pthread_join(threads[0], NULL);
		return (ERROR);
	}
	info->data->start_time_t = ft_get_time();
	pthread_mutex_unlock(&info->data->prog_m[START]);
	return (SUCCESS);
}

int	handle_one(t_god *info, pthread_t *threads)
{
	if (create_one_philo(info, threads))
	{
		free(threads);
		destroy_everything(info);
		return (ft_error("thread creation for one failed"));
	}
	monitor(info);
	pthread_join(threads[0], NULL);
	free(threads);
	destroy_everything(info);
	return (SUCCESS);
}
