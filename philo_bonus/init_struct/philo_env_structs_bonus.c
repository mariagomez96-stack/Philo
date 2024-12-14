/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_env_structs_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:08:19 by marigome          #+#    #+#             */
/*   Updated: 2024/12/14 11:39:54 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_init_semaphores(t_envp *envp)
{
	int	i;

	envp->forks = malloc(sizeof(sem_t) * envp->nbr_philos);
	if (!envp->forks)
		return (EXIT_FAILURE);
	for (i = 0; i < envp->nbr_philos; i++)
		sem_init(&envp->forks[i], 0, 1);
	sem_init(envp->mealtime, 0, 1);
	sem_init(&envp->writing, 0, 1);
	return (EXIT_SUCCESS);
}

int	ft_init_philo(t_envp *envp)
{
	int	i;

	for (i = 0; i < envp->nbr_philos; i++)
	{
		envp->philos[i].pos = i + 1;
		envp->philos[i].times_eaten = 0;
		envp->philos[i].pos_char = ft_philo_itoa(i + 1);
		if (!envp->philos[i].pos_char)
			return (EXIT_FAILURE);
		envp->philos[i].envp = envp;
	}
	return (EXIT_SUCCESS);
}

int	ft_init_sim(t_envp *envp)
{
	envp->philos = malloc(sizeof(t_philo) * envp->nbr_philos);
	if (!envp->philos)
		return (EXIT_FAILURE);
	if (ft_init_semaphores(envp) || ft_init_philo(envp))
	{
		free(envp->philos);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

