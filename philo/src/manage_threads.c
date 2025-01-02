/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:41:20 by marigome          #+#    #+#             */
/*   Updated: 2025/01/02 09:13:54 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*ft_routine(void *args)
{
	t_philo	*philo;
	t_data	*data;
	int		stop_flag;
	int		max_ate_flag;

	philo = (t_philo *)args;
	data = philo->data;
	if (philo->id % 2 && data->philo_count > 1)
		ft_sleep(data->time_to_eat * 2, data);
	while (1)
	{
		stop_flag = ft_lock_stop_flag(data);
		pthread_mutex_lock(&data->mutex_max_ate);
		max_ate_flag = data->max_ate;
		pthread_mutex_unlock(&data->mutex_max_ate);
		if (stop_flag || max_ate_flag)
			break ;
		ft_eat(philo);
		ft_check_status(SLEEP, philo, UNLOCK, data);
		ft_sleep(data->time_to_sleep, data);
		ft_check_status(THINK, philo, UNLOCK, data);
	}
	return (NULL);
}

static void	ft_exit(t_data *data)
{
	int	i;

	if (data->philo_count == 1)
		pthread_detach(data->philos[0].thread_id);
	else
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_join(data->philos[i].thread_id, NULL);
			i++;
		}
	}
	ft_destroy_mutex(data);
	ft_free_philo(data);
}

static int	ft_create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->start = ft_get_time();
	while (i < data->philo_count)
	{
		data->philos[i].last_eat = ft_get_time();
		if (pthread_create(&data->philos[i].thread_id, NULL, \
		ft_routine, &(data->philos[i])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_thread(t_data *data)
{
	if (!ft_create_thread(data))
		return (0);
	ft_dead(data, data->philos);
	pthread_mutex_lock(&data->print);
	pthread_mutex_unlock(&data->print);
	ft_exit(data);
	return (1);
}
