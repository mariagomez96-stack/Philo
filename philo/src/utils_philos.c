/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:50:46 by marigome          #+#    #+#             */
/*   Updated: 2024/12/20 20:40:32 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_sleep(unsigned long time, t_data *data)
{
	unsigned long	start;
	int				stop_flag;

	start = ft_get_time();
	while (1)
	{
		// Proteger la lectura de `stopping`
		pthread_mutex_lock(&data->stopping_mutex);
		stop_flag = data->stopping; // Leer el valor protegido
		pthread_mutex_unlock(&data->stopping_mutex);

		// Salir del bucle si `stopping` está activado
		if (stop_flag)
			break;

		// Salir del bucle si el tiempo ha transcurrido
		if (ft_get_time() - start >= time)
			break;

		// Reducir el consumo de CPU
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
}*/

/*void	ft_check_status(char *mesg, t_philo *philo, int lock)
{
	char			*timestatus;
	unsigned long	current_time;
	int				adjusted_time;
	int				stop_flag;
	int				max_ate_flag;

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

	// Proteger la lectura de stopping y max_ate
	pthread_mutex_lock(&philo->data->stopping_mutex);
	stop_flag = philo->data->stopping;
	pthread_mutex_unlock(&philo->data->stopping_mutex);

	pthread_mutex_lock(&philo->data->mutex_max_ate);
	max_ate_flag = philo->data->max_ate;
	pthread_mutex_unlock(&philo->data->mutex_max_ate);

	// Imprimir solo si stopping y max_ate no están activados
	pthread_mutex_lock(&philo->data->print);
	if (!stop_flag && !max_ate_flag)
		printf("%s %s %s\n", timestatus, philo->status, mesg);
	if (lock)
		pthread_mutex_unlock(&philo->data->print);

	free(timestatus);
}*/

void	ft_check_status(char *mesg, t_philo *philo, int lock)
{
	char			*timestatus;
	unsigned long	current_time;
	int				stop_flag;
	int				max_ate_flag;


	current_time = ft_get_time();
	timestatus = ft_itoa(current_time - philo->data->start);
	if (ft_strcmp(mesg, DEAD) == 0)
		return (ft_print_dead(philo, mesg), free(timestatus));
	pthread_mutex_lock(&philo->data->print); //Nuevo por mutex
	philo->last_time_status = atoi(timestatus);
	pthread_mutex_unlock(&philo->data->print); // Nuevo por mutex
	pthread_mutex_lock(&philo->data->stopping_mutex);
	stop_flag = philo->data->stopping;
	pthread_mutex_unlock(&philo->data->stopping_mutex);
	pthread_mutex_lock(&philo->data->mutex_max_ate);
	max_ate_flag = philo->data->max_ate;
	pthread_mutex_unlock(&philo->data->mutex_max_ate);
	pthread_mutex_lock(&philo->data->print);
	if (!stop_flag && !max_ate_flag)
		printf("%s %s %s\n", timestatus, philo->status, mesg);
	if (lock)
		pthread_mutex_unlock(&philo->data->print);
}

/*void	ft_dead(t_data *data, t_philo *philo)
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
}*/

/*void	ft_dead(t_data *data, t_philo *philo)
{
	int	i;
	int	stop_flag;
	int	max_ate_flag;

	while (1)
	{
		i = 0;
		max_ate_flag = ft_ate_flag(data);
		if (max_ate_flag)
			break;
		while (i < data->philo_count)
		{
			stop_flag = ft_lock_stop_flag(data);
			if (stop_flag)
				break;
			ft_dead_util(philo, data, i);
			i++;
		}
		usleep(100);
		stop_flag = ft_lock_stop_flag(data);
		if (stop_flag)
			break;
		ft_check_max_eat(data, philo);
	}
}*/

void	ft_dead(t_data *data, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		if (ft_ate_flag(data))
			return ;
		if (ft_lock_stop_flag(data))
			return ;
		while (i < data->philo_count)
		{
			ft_dead_util(philo, data, i);
			if (ft_lock_stop_flag(data))
				return ;
			i++;
		}
		ft_check_max_eat(data, philo);
	}
}

void	ft_eat(t_philo *philo)
{
	if (philo->right_fork < philo->left_fork)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	}
	ft_check_status(TAKEN_FORK, philo, UNLOCK);
	ft_check_status(TAKEN_FORK, philo, UNLOCK);
	pthread_mutex_lock(&philo->data->mealtime);
	ft_check_status(EAT, philo, UNLOCK);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->data->mealtime);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	ft_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->eat_count_mutex);
}




