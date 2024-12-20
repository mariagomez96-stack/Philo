/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:05:18 by marigome          #+#    #+#             */
/*   Updated: 2024/12/20 20:38:30 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].eat_count_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->mealtime);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->stopping_mutex);
	pthread_mutex_destroy(&data->mutex_max_ate);
}

void	ft_free_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		free(data->philos[i].status);
	free(data->philos);
	free(data->forks);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		neg;
	long	value;

	i = 0;
	value = 0;
	neg = 0;
	while ((nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-')
		neg = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= 48 && nptr[i] <= 57)
	{
		if (value >= 922337203685477580 || (value == 922337203685477580
				&& ((!neg && nptr[i] - '0' > 7) || (neg && nptr[i] - '0' > 8))))
			return (-1 * !neg);
		else
			value = (value * 10) + nptr[i++] - '0';
	}
	if (neg)
		value = -value;
	return (value);
}

void ft_print_dead(t_philo *philo, char *mesg)
{
	int	adjusted_time;

	pthread_mutex_lock(&philo->data->print);
	adjusted_time = philo->last_time_status + 10;
	printf("%d %d %s\n", adjusted_time, philo->id, mesg);
	pthread_mutex_unlock(&philo->data->print);
}

