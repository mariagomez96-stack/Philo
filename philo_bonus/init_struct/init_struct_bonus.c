/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:08:36 by marigome          #+#    #+#             */
/*   Updated: 2024/12/21 10:18:43 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	ft_init_env(int argc, char **argv, t_data *env)
{
	env->death = NULL;
	env->stop = NULL;
	env->print = NULL;
	env->forks = NULL;
	env->philo_count = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	env->max_eat = -1;
	env->current_eat = -1;
	env->eat_counter = -1;
	if (argc == 6)
	{
		env->eat_counter = 0;
		env->current_eat = 0;
		env->max_eat = ft_atoi(argv[5]);
	}
	return (0);
}

t_philo	*ft_init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->philo_count);
	while (i < data->philo_count)
	{
		philo[i].id = i;
		philo[i].pid = -1;
		philo[i].death = 0;
		philo[i].data = data;
		philo[i].eat_count = data->eat_counter;
		philo[i].last_time_status = 0;
		i++;
	}
	return (philo);
}
