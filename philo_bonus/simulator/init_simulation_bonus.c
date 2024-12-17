/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:28:15 by marigome          #+#    #+#             */
/*   Updated: 2024/12/17 12:16:10 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static void ft_create_semaphores(t_data *data)
{
    sem_unlink("death");
    sem_unlink("print");
    sem_unlink("forks");
    sem_unlink("stop");
    data->death = sem_open("death", O_CREAT, 0600, 1);
    data->print = sem_open("print", O_CREAT, 0600, 1);
    data->forks = sem_open("forks", O_CREAT, 0600, data->philo_count);
    data->stop = sem_open("stop", O_CREAT, 0600, 1);
}


void  ft_init_simulation(t_data *data, t_philo *philo)
{
    int i;

    i = 0;
    data->start = ft_get_time();
    data->philos = philo;
    ft_create_semaphores(data);
    sem_wait(data->stop);
    while (i < data->philo_count)
    {
        philo[i].pid = fork();
        if (philo[i].pid == 0)
        {
            ft_routine(philo + i);
            exit(0);
        }
        i++;
        usleep(100);
    }

}

void	ft_destroy_all(t_data *simulation, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < simulation->philo_count)
		kill(philo[i++].pid, SIGKILL);
	sem_close(simulation->death);
	sem_close(simulation->print);
	sem_close(simulation->stop);
	sem_close(simulation->forks);
	free(philo);
}