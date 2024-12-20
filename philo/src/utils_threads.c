/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:02:17 by marigome          #+#    #+#             */
/*   Updated: 2024/12/20 19:42:54 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int ft_lock_stop_flag(t_data *data)
{
    int stop_flag;
    pthread_mutex_lock(&data->stopping_mutex);
    stop_flag = data->stopping;
    pthread_mutex_unlock(&data->stopping_mutex);
    return(stop_flag);
}

void ft_check_dead_flag(t_philo *philo, t_data *data)
{
    ft_check_status(DEAD, philo, LOCK);
	pthread_mutex_lock(&data->stopping_mutex);
	data->stopping = 1;
	pthread_mutex_unlock(&data->stopping_mutex);
}

void	ft_lock_mutex_ate(t_data *data, int i)
{
	pthread_mutex_lock(&data->mutex_max_ate);
	data->max_ate = (i == data->philo_count);
	pthread_mutex_unlock(&data->mutex_max_ate);
}

void	ft_check_max_eat(t_data *data, t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].eat_count_mutex);
	if (philo[i].eat_count < data->eat_count_max)
	{
		pthread_mutex_unlock(&philo[i].eat_count_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo[i].eat_count_mutex);
}