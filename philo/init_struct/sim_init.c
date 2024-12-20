/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:11:18 by marigome          #+#    #+#             */
/*   Updated: 2024/12/20 18:47:36 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	ft_init_fork(t_data *env)
{
	int	i;

	i = 0;
	while (i < env->philo_count)
	{
		if (pthread_mutex_init(&(env->forks[i]), NULL))
			return (1);
		if (pthread_mutex_init(&(env->philos[i].eat_count_mutex), NULL))
			return (1);
		i++;
	}
	return (0);
}

static int	ft_init_mealtime_and_print_mutex(t_data *env)
{
	if (pthread_mutex_init(&(env->mealtime), NULL))
		return (1);
	if (pthread_mutex_init(&(env->print), NULL))
		return (1);
	if (pthread_mutex_init(&(env->stopping_mutex), NULL))
		return (1);
	if (pthread_mutex_init(&(env->mutex_max_ate), NULL))
		return (1);
	return (0);
}

int	ft_init_philo_sim(t_data *env)
{
	env->philos = (t_philo *)malloc(sizeof(t_philo) * env->philo_count);
	if (!env->philos)
		return (0);
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* env->philo_count);
	if (!env->forks)
		return (free(env->philos), 0);
	if (ft_init_fork(env) || ft_init_mealtime_and_print_mutex(env) \
	|| ft_init_philos(env))
	{
		free(env->philos);
		free(env->forks);
		return (0);
	}
	return (1);
}
