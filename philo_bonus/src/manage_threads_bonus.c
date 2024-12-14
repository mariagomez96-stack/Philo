/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:41:20 by marigome          #+#    #+#             */
/*   Updated: 2024/12/14 11:37:37 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_destroy_semaphores_and_free(t_envp *envp)
{
	int	i;

	for (i = 0; i < envp->nbr_philos; i++)
		free(envp->philos[i].pos_char);
	free(envp->philos);
	for (i = 0; i < envp->nbr_philos; i++)
		sem_destroy(&envp->forks[i]);
	free(envp->forks);
	sem_destroy(envp->mealtime);
	sem_destroy(&envp->writing);
}

int	ft_isinteger(char *nbr)
{
	long	result;

	result = 0;
	result = ft_philo_atoi(nbr);
	if (result <= INTMAX || result >= INTMIN)
		return (1);
	else
		return (0);
}


void	ft_sleep(unsigned long total_time, t_envp *envp)
{
	unsigned long	init;

	init = ft_get_time();
	while (!envp->stopping_rule)
	{
		if (ft_get_time() - init >= total_time)
			break ;
		usleep(envp->nbr_philos * 2);
	}
	// return ;
}




