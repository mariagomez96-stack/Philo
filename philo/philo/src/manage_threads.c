/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:41:20 by marigome          #+#    #+#             */
/*   Updated: 2024/12/20 11:57:59 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_check_death(t_philo *philo)
{
	unsigned long	current_time;

	// Obtener el tiempo actual
	current_time = ft_get_time();

	// Verificar si el filósofo ha excedido time_to_die
	if ((current_time - philo->data->time_to_die) <= (unsigned long)philo->data->time_to_die)
	{
		ft_check_status(DEAD, philo, LOCK); // Imprimir la muerte
		philo->data->stopping = 1; // Detener la simulación
		return (1); // Ha muerto
	}

	// Si no ha muerto, retornar 0
	return (0);
}


static void	*ft_routine(void *args)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)args;
	data = philo->data;
	if (philo->id % 2 && data->philo_count > 1)
		ft_sleep(data->time_to_eat / 50, data);
	while (!data->stopping && !data->max_ate)
	{
		ft_check_death(philo);
		ft_eat(philo);
		ft_sleep(data->time_to_sleep / 2, data);
		ft_check_status(SLEEP, philo, UNLOCK);
		ft_think(data->time_to_think / 2, data);
		ft_check_status(THINK, philo, UNLOCK);
	}
	return (NULL);
}

static void	ft_exit(t_data *data)
{
	int	i;

	if (data->philo_count == 1)
		pthread_detach(data->philos[0].thread_id);
	else
	{
		i = 0;
		while (i < data->philo_count)
		{
			pthread_join(data->philos[i].thread_id, NULL);
			i++;
		}
	}
	ft_destroy_mutex(data);
	ft_free_philo(data);
}

static int	ft_create_thread(t_data *data)
{
	int	i;

	i = 0;
	data->start = ft_get_time();
	while (i < data->philo_count)
	{
		data->philos[i].last_eat = ft_get_time();
		if (pthread_create(&data->philos[i].thread_id, NULL, \
		ft_routine, &(data->philos[i])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_thread(t_data *data)
{
	if (!ft_create_thread(data))
		return (0);
	ft_dead(data, data->philos);
	pthread_mutex_unlock(&data->print);
	ft_exit(data);
	return (1);
}
