/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:41:20 by marigome          #+#    #+#             */
/*   Updated: 2024/12/12 12:40:18 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	*ft_routine(void *args)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)args;
	data = philo->data;
	if (philo->id % 2 && data->philo_count > 1)
		ft_sleep(data->time_to_eat / 50, data);
	while (!data->stopping && !data->max_ate)
	{
		ft_eat(philo);
		ft_check_status(SLEEP, philo, UNLOCK);
		ft_sleep(data->time_to_sleep, data);
		ft_check_status(THINK, philo, UNLOCK);
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
		i = -1;
		while (++i < data->philo_count)
			pthread_join(data->philos[i].thread_id, NULL);
	}
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->mealtime);
	pthread_mutex_destroy(&data->print);
	i = -1;
	while (++i < data->philo_count)
		free(data->philos[i].status);
	free(data->philos);
	free(data->forks);
}

int	ft_create_thread(t_data *data)
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
	ft_dead(data, data->philos);
	pthread_mutex_unlock(&data->print);
	ft_exit(data);
	return (1);
}
