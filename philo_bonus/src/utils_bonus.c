/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:28:24 by marigome          #+#    #+#             */
/*   Updated: 2024/12/17 13:11:15 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	ft_atoi(char *nptr)
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

int	ft_error(t_data *data, char *message, int ret)
{
	if (data)
	{
		if (data->forks)
			free(data->forks);
	}
	printf("%s\n", message);
	return (ret);
}

unsigned int	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (unsigned long)1000) + (time.tv_usec / 1000));
}

void	ft_print_message(char *id, t_philo *philo)
{
	unsigned int	time;

	time = ft_get_time() - philo->data->start;
	sem_wait(philo->data->print);
	if (!ft_strcmp(id, TAKEN_FORK))
		printf("%u\t%d %s\n", time, philo->id + 1, TAKEN_FORK);
	else if (!ft_strcmp(id, EAT))
		printf("%u\t%d %s\n", time, philo->id + 1, EAT);
	else if (!ft_strcmp(id, SLEEP))
		printf("%u\t%d %s\n", time, philo->id + 1, SLEEP);
	else if (!ft_strcmp(id, THINK))
		printf("%u\t%d %s\n", time, philo->id + 1, THINK);
	else if (!ft_strcmp(id, DEAD))
		printf("%u\t%d %s\n", time, philo->id + 1, DEAD);
	else if (!ft_strcmp(id, DONE))
		printf("%s\n", DONE);
	if (ft_strcmp(id, DEAD) != 0) // Solo liberamos el semáforo si no está muerto
		sem_post(philo->data->print);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i]) // Mientras no lleguemos al final de ninguna cadena
	{
		if (s1[i] != s2[i]) // Si los caracteres no coinciden
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	// Si las cadenas son de diferente longitud, devolvemos la diferencia
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

