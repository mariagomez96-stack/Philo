/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:11:18 by marigome          #+#    #+#             */
/*   Updated: 2024/12/12 08:37:32 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_init_mutex(t_data *env)
{
	int i;

	i = 0;
	while (i < env->philo_count)
	{
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&env->mealtime, NULL))
		return (1);
	if (pthread_mutex_init(&env->print, NULL))
		return (1);
	return (0);
}

int	ft_init_philo_sim(t_data *env)
{
	env->philos = (t_philo *)malloc(sizeof(t_philo) * env->philo_count);
	if (!env->philos)
		return (0);
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * env->philo_count);
	if (!env->forks)
		return (free(env->philos), 0);
	if (ft_init_mutex(env))
	{
		free(env->philos);
		free(env->forks);
		return (0);
	}
	if (ft_init_philos(env))
	{
		free(env->philos);
		free(env->forks);
		return (0);
	}
	return (1);
}
