/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:52 by marigome          #+#    #+#             */
/*   Updated: 2024/12/17 14:09:40 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	*ft_check_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->death);
		if (philo->next_meal < ft_get_time())
		{
			ft_print_message(DEAD, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
		sem_wait(philo->data->death);
		if (philo->data->current_eat != -1 && philo->eat_count >= philo->data->max_eat)
		{
			ft_print_message(DONE, philo);
			sem_post(philo->data->stop);
			break ;
		}
		sem_post(philo->data->death);
	}
	return (NULL);
}


void	ft_take_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_print_message("Has taken a fork", philo);
	sem_wait(philo->data->forks);
	ft_print_message("Has taken a fork", philo);
}

/*void	ft_eat(t_philo *philo)
{
	ft_print_message(EAT, philo);
	if (philo->data->eat_counter != -1)
		philo->data->current_eat++;
	usleep(philo->data->time_to_eat * 1000);
	philo->last_meal = ft_get_time();
	philo->next_meal = philo->last_meal
		+ (unsigned int)philo->data->time_to_die;
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}*/

void	ft_eat(t_philo *philo)
{
	// Tomar los tenedores
	sem_wait(philo->data->forks); // Tomar primer tenedor
	ft_print_message(TAKEN_FORK, philo);
	sem_wait(philo->data->forks); // Tomar segundo tenedor
	ft_print_message(TAKEN_FORK, philo);

	// Actualizar el estado del filósofo a "EAT"
	sem_wait(philo->data->death); // Proteger acceso a las variables críticas
	ft_print_message(EAT, philo);

	philo->last_meal = ft_get_time(); // Registrar tiempo de última comida
	philo->next_meal = philo->last_meal + philo->data->time_to_die;

	philo->eat_count++; // Incrementar el contador individual de comidas
	printf("Filosofo: %d, Comidas: %d\n", philo->id, philo->eat_count);
	if (philo->data->eat_counter != -1 && philo->eat_count >= philo->data->eat_counter)
		philo->data->current_eat++; // Actualizar contador global

	sem_post(philo->data->death); // Desbloquear acceso a las variables críticas

	// Simular el tiempo de comer
	usleep(philo->data->time_to_eat * 1000);

	// Devolver los tenedores
	sem_post(philo->data->forks); // Liberar primer tenedor
	sem_post(philo->data->forks); // Liberar segundo tenedor
}



void	ft_sleep(t_philo *philo)
{
	ft_print_message(SLEEP, philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	ft_routine(t_philo *philo)
{
	pthread_t	death;

	philo->next_meal = ft_get_time() + (unsigned int)philo->data->time_to_die;
	pthread_create(&death, NULL, ft_check_death, philo);
	pthread_detach(death);
	while (1)
	{
		//ft_take_fork(philo);
		ft_eat(philo);
		ft_sleep(philo);
		//ft_print_message(THINK, philo);
	}
}