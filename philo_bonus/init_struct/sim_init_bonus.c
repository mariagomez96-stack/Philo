/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:11:18 by marigome          #+#    #+#             */
/*   Updated: 2024/12/14 11:44:44 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_init_struct(t_envp *envp, int argc, char *argv[])
{
	envp->nbr_philos = 0;
	envp->time_to_die = 0;
	envp->time_to_eat = 0;
	envp->time_to_sleep = 0;
	envp->philo_eat_limit = 0;
	envp->nbr_philos = ft_philo_atoi(argv[1]);
	envp->time_to_die = ft_philo_atoi(argv[2]);
	envp->time_to_eat = ft_philo_atoi(argv[3]);
	envp->time_to_sleep = ft_philo_atoi(argv[4]);
	if (argc == 6)
		envp->philo_eat_limit = ft_philo_atoi(argv[5]);
}

int	ft_create_threads_and_monitor(t_envp *envp)
{
	int	i;

	i = 0;
	envp->init_time = ft_get_time();
	while (i < envp->nbr_philos)
	{
		envp->philos[i].last_meal = ft_get_time();
		// Crear los hilos para cada filósofo
		if (pthread_create(&envp->philos[i].thread_id, NULL, \
		ft_philosopher_routine, &(envp->philos[i])))
			return (EXIT_FAILURE);
		i++;
	}
	// Monitorizar las muertes de los filósofos
	ft_check_dead(envp, envp->philos);
	
	// No es necesario "desbloquear" semáforos aquí, pero si es un requisito,
	// asegúrate de liberar correctamente semáforos globales si los usas.
	sem_post(&envp->writing); // Desbloquear el semáforo global de escritura si es necesario

	// Finalizar los hilos
	ft_exit_threads(envp);
	return (EXIT_SUCCESS);
}

