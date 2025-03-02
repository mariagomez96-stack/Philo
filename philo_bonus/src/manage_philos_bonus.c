/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philos_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 11:43:52 by marigome          #+#    #+#             */
/*   Updated: 2024/12/21 10:49:28 by marigome         ###   ########.fr       */
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
			sem_post(philo->data->death);
			break ;
		}
		if (philo->data->current_eat != -1 && \
		philo->eat_count >= philo->data->max_eat + 1)
		{
			sem_post(philo->data->stop);
			sem_post(philo->data->death);
			break ;
		}
		sem_post(philo->data->death);
		usleep(100);
	}
	return (NULL);
}

void	ft_take_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	ft_print_message(TAKEN_FORK, philo);
	usleep(100);
	sem_wait(philo->data->forks);
	ft_print_message(TAKEN_FORK, philo);
}

void	ft_eat(t_philo *philo)
{
	ft_take_fork(philo);
	ft_print_message(EAT, philo);
	sem_wait(philo->data->death);
	philo->last_meal = ft_get_time();
	philo->next_meal = philo->last_meal + \
	(unsigned int)philo->data->time_to_die;
	sem_post(philo->data->death);
	philo->eat_count++;
	if (philo->data->eat_counter != -1 \
	&& philo->eat_count >= philo->data->eat_counter)
		philo->data->current_eat++;
	sem_post(philo->data->death);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_message(SLEEP, philo);
	if (philo->id % 2 && philo->data->philo_count > 1)
		usleep(philo->data->time_to_eat / 50);
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
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		usleep(500);
	}
}
