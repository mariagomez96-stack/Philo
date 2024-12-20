/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:05:18 by marigome          #+#    #+#             */
/*   Updated: 2024/12/20 18:51:03 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].eat_count_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->mealtime);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->stopping_mutex);
	pthread_mutex_destroy(&data->mutex_max_ate);
}

void	ft_free_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		free(data->philos[i].status);
	free(data->philos);
	free(data->forks);
}
