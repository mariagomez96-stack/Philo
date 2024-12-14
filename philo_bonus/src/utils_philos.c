/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:50:46 by marigome          #+#    #+#             */
/*   Updated: 2024/12/13 11:27:59 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_sleep(unsigned long time, t_data *data)
{
	unsigned long	start;

	start = ft_get_time();
	while (!data->stopping)
	{
		if (ft_get_time() - start >= time)
			break ;
		usleep(data->philo_count * 3);
	}
}

void	ft_think(unsigned long time, t_data *data)
{
	ft_sleep(time, data);
}

void	ft_check_status(char *mesg, t_philo *philo, int lock)
{
	char	*timestatus;

	timestatus = ft_itoa(ft_get_time() - philo->data->start);
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->stopping && !philo->data->max_ate)
		printf("%s %s %s\n", timestatus, philo->status, mesg);
	if (lock)
		pthread_mutex_unlock(&philo->data->print);
	free(timestatus);
}

void	ft_dead(t_data *data, t_philo *philo)
{
	int	i;

	while (!data->max_ate)
	{
		i = 0;
		while (i < data->philo_count && !data->stopping)
		{
			pthread_mutex_lock(&data->mealtime);
			if ((int)(ft_get_time() - philo[i].last_eat) >= data->time_to_die)
			{
				ft_check_status(DEAD, &philo[i], LOCK);
				data->stopping = 1;
			}
			pthread_mutex_unlock(&data->mealtime);
			i++;
		}
		if (data->stopping)
			break ;
		i = 0;
		while (data->eat_count_max && i < data->philo_count
			&& philo[i].eat_count >= data->eat_count_max)
			i++;
		data->max_ate = (i == data->philo_count);
	}
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	ft_check_status(TAKEN_FORK, philo, UNLOCK);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	ft_check_status(TAKEN_FORK, philo, UNLOCK);
	pthread_mutex_lock(&philo->data->mealtime);
	ft_check_status(EAT, philo, UNLOCK);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->data->mealtime);
	ft_sleep(philo->data->time_to_eat, philo->data);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}
