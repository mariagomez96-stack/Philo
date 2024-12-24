/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:02:17 by marigome          #+#    #+#             */
/*   Updated: 2024/12/24 11:19:49 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_lock_stop_flag(t_data *data)
{
	int	stop_flag;

	pthread_mutex_lock(&data->stopping_mutex);
	stop_flag = data->stopping;
	pthread_mutex_unlock(&data->stopping_mutex);
	return (stop_flag);
}

void	ft_check_dead_flag(t_philo *philo, t_data *data)
{
	ft_check_status(DEAD, philo, LOCK, data);
	pthread_mutex_lock(&data->stopping_mutex);
	data->stopping = 1;
	pthread_mutex_unlock(&data->stopping_mutex);
}

int	ft_ate_flag(t_data *data)
{
	int	max_ate_flag;

	pthread_mutex_lock(&data->mutex_max_ate);
	max_ate_flag = data->max_ate;
	pthread_mutex_unlock(&data->mutex_max_ate);
	return (max_ate_flag);
}

void	ft_check_max_eat(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (data->eat_count_max && i < data->philo_count)
	{
		pthread_mutex_lock(&philo[i].eat_count_mutex);
		if (philo[i].eat_count < data->eat_count_max)
		{
			pthread_mutex_unlock(&philo[i].eat_count_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo[i].eat_count_mutex);
		i++;
	}
	pthread_mutex_lock(&data->mutex_max_ate);
	data->max_ate = (i == data->philo_count);
	pthread_mutex_unlock(&data->mutex_max_ate);
}

void	ft_dead_util(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_lock(&data->mealtime);
	if ((int)(ft_get_time() - philo->last_eat) >= data->time_to_die)
		ft_check_dead_flag(&philo[i], data);
	pthread_mutex_unlock(&data->mealtime);
}
