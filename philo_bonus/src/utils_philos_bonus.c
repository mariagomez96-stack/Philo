/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:50:46 by marigome          #+#    #+#             */
/*   Updated: 2024/12/14 11:39:27 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_check_eat(t_philo *philo)
{
	t_envp	*envp;

	envp = philo->envp;
	sem_wait(&envp->forks[philo->pos - 1]);
	ft_check_stamp("TAKEN_FORK", philo, 0);
	sem_wait(&envp->forks[philo->pos % envp->nbr_philos]);
	ft_check_stamp( "TAKEN_FORK", philo, 0);

	sem_wait(envp->mealtime);
	ft_check_stamp("EAT", philo, 0);
	philo->last_meal = ft_get_time();
	sem_post(envp->mealtime);

	ft_sleep(envp->time_to_eat, envp);
	philo->times_eaten++;

	sem_post(&envp->forks[philo->pos - 1]);
	sem_post(&envp->forks[philo->pos % envp->nbr_philos]);
}

void	ft_check_stamp(char *msg, t_philo *philo, int unlock)
{
	char	*timestamp;

	timestamp = ft_philo_itoa(ft_get_time() - philo->envp->init_time);
	if (!timestamp)
		return ;
	sem_wait(&philo->envp->writing);
	if (!philo->envp->stopping_rule && !philo->envp->eat_max)
		printf("%s %s %s\n", timestamp, philo->pos_char, msg);
	if (unlock)
		sem_post(&philo->envp->writing);
	free(timestamp);
}

void	ft_check_dead(t_envp *envp, t_philo *philo)
{
	int	i;
	int	all_philos_full;

	while (!envp->eat_max)
	{
		all_philos_full = 1;
		for (i = 0; i < envp->nbr_philos; i++)
		{
			sem_wait(envp->mealtime);
			if ((int)(ft_get_time() - philo[i].last_meal) >= envp->time_to_die)
			{
				ft_check_stamp("DIED", &philo[i], 1);
				envp->stopping_rule = 1;
			}
			sem_post(envp->mealtime);
			if (envp->philo_eat_limit && philo[i].times_eaten \
			< envp->philo_eat_limit)
				all_philos_full = 0;
		}
		if (envp->stopping_rule)
			break ;
		envp->eat_max = all_philos_full;
	}
}



