/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:50:46 by marigome          #+#    #+#             */
/*   Updated: 2025/01/02 09:14:09 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_sleep(unsigned long time, t_data *data)
{
	unsigned long	start;
	int				stop_flag;

	start = ft_get_time();
	while (1)
	{
		pthread_mutex_lock(&data->stopping_mutex);
		stop_flag = data->stopping;
		pthread_mutex_unlock(&data->stopping_mutex);
		if (stop_flag)
			break ;
		if (ft_get_time() - start >= time)
			break ;
		usleep(100);
	}
}

void	ft_think(unsigned long time, t_data *data)
{
	ft_sleep(time, data);
}

void	ft_check_status(char *mesg, t_philo *philo, int lock, t_data *data)
{
	char			*timestatus;
	unsigned long	current_time;
	int				stop_flag;
	int				max_ate_flag;

	current_time = ft_get_time();
	timestatus = ft_itoa(current_time - philo->data->start);
	if (ft_strcmp(mesg, DEAD) == 0)
		return (ft_print_dead(philo, mesg, data));
	pthread_mutex_lock(&philo->data->print);
	data->last_time_status = atoi(timestatus);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->data->stopping_mutex);
	stop_flag = philo->data->stopping;
	pthread_mutex_unlock(&philo->data->stopping_mutex);
	pthread_mutex_lock(&philo->data->mutex_max_ate);
	max_ate_flag = philo->data->max_ate;
	pthread_mutex_unlock(&philo->data->mutex_max_ate);
	pthread_mutex_lock(&philo->data->print);
	if (!stop_flag && !max_ate_flag)
		printf("%s %s %s\n", timestatus, philo->status, mesg);
	if (lock)
		pthread_mutex_unlock(&philo->data->print);
}

void	ft_dead(t_data *data, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		if (ft_ate_flag(data))
			return ;
		if (ft_lock_stop_flag(data))
			return ;
		while (i < data->philo_count)
		{
			ft_dead_util(philo, data, i);
			if (ft_lock_stop_flag(data))
				return ;
			i++;
		}
		ft_check_max_eat(data, philo);
	}
}

void	ft_eat(t_philo *philo)
{
	if (philo->right_fork < philo->left_fork)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	}
	ft_check_status(TAKEN_FORK, philo, UNLOCK, philo->data);
	ft_check_status(TAKEN_FORK, philo, UNLOCK, philo->data);
	pthread_mutex_lock(&philo->data->mealtime);
	ft_check_status(EAT, philo, UNLOCK, philo->data);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->data->mealtime);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	ft_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
}
