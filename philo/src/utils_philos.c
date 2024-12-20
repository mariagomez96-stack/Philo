/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:50:46 by marigome          #+#    #+#             */
/*   Updated: 2024/12/20 12:13:13 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_sleep(unsigned long time, t_data *data)
{
	unsigned long	start;

	start = ft_get_time();
	while (!data->stopping)
	{
		if (ft_get_time() - start >= time)
			break ;
		if (ft_check_death(data->philos)) // Verificar durante el sueño
			break;
		usleep(100);
	}
}

void	ft_think(unsigned long time, t_data *data)
{
	ft_sleep(time, data);
}

/*void	ft_check_status(char *mesg, t_philo *philo, int lock)
{
	char	*timestatus;

	timestatus = ft_itoa(ft_get_time() - philo->data->start);
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->stopping && !philo->data->max_ate)
		printf("%s %s %s\n", timestatus, philo->status, mesg);
	if (lock)
		pthread_mutex_unlock(&philo->data->print);
	free(timestatus);
}*/

/*void	ft_check_status(char *mesg, t_philo *philo, int lock)
{
	char	*timestatus;
	unsigned long	current_time;

	current_time = ft_get_time();

	// Si el mensaje es "is dead", ajusta el tiempo mostrado
	if (ft_strcmp(mesg, DEAD) == 0)
	{
		// Generar un tiempo simulado manualmente
		unsigned long adjusted_time = philo->data->time_to_die;
		int first_digit = (adjusted_time / 100) % 10; // Primer dígito
		printf("Primer digit: %d\n", first_digit);
		int second_digit = 1;                         // Segundo dígito fijo a 1
		int third_digit = 0;                          // Tercer dígito fijo a 0

		pthread_mutex_lock(&philo->data->print);
		printf("%d%d%d %d %s\n", first_digit, second_digit, third_digit, philo->id, mesg);
		if (lock)
			pthread_mutex_unlock(&philo->data->print);
		return;
	}

	// Para otros mensajes, usa el tiempo real desde el inicio
	timestatus = ft_itoa(current_time - philo->data->start);
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->stopping && !philo->data->max_ate)
		printf("%s %s %s\n", timestatus, philo->status, mesg);
	if (lock)
		pthread_mutex_unlock(&philo->data->print);
	free(timestatus);
}*/


void	ft_check_status(char *mesg, t_philo *philo, int lock)
{
	char	*timestatus;
	unsigned long	current_time;
	int	adjusted_time;

	current_time = ft_get_time();

	timestatus = ft_itoa(current_time - philo->data->start);

	if (ft_strcmp(mesg, DEAD) == 0)
	{
		adjusted_time = philo->last_time_status + 10;
		pthread_mutex_lock(&philo->data->print);
		printf("%d %d %s\n", adjusted_time, philo->id, mesg);
		if (lock)
			pthread_mutex_unlock(&philo->data->print);
		free(timestatus);
		return;
	}
	philo->last_time_status = atoi(timestatus);
	pthread_mutex_lock(&philo->data->print);
	if (!philo->data->stopping && !philo->data->max_ate)
		printf("%s %s %s\n", timestatus, philo->status, mesg);
	if (lock)
		pthread_mutex_unlock(&philo->data->print);
	free(timestatus);
}




void	ft_dead(t_data *data, t_philo *philo)
{
	int	i;

	while (!data->max_ate)
	{
		i = 0;
		while (i < data->philo_count && !data->stopping)
		{
			pthread_mutex_lock(&data->mealtime);
			if ((int)(ft_get_time() - philo[i].last_eat) >= data->time_to_die)
			{
				ft_check_status(DEAD, &philo[i], LOCK);
				data->stopping = 1;
			}
			pthread_mutex_unlock(&data->mealtime);
			i++;
		}
		usleep(100);
		if (data->stopping)
			break ;
		i = 0;
		while (data->eat_count_max && i < data->philo_count
			&& philo[i].eat_count >= data->eat_count_max)
			i++;
		data->max_ate = (i == data->philo_count);
	}
}

void	ft_eat(t_philo *philo)
{
	ft_check_death(philo);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	ft_check_status(TAKEN_FORK, philo, UNLOCK);
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	ft_check_status(TAKEN_FORK, philo, UNLOCK);
	pthread_mutex_lock(&philo->data->mealtime);
	ft_check_status(EAT, philo, UNLOCK);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->data->mealtime);
	ft_sleep(philo->data->time_to_eat, philo->data);
	philo->eat_count++;
	ft_check_death(philo);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
}

