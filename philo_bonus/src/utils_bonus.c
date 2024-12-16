/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:58:10 by marigome          #+#    #+#             */
/*   Updated: 2024/12/16 13:44:48 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"


int	ft_msg_err(char *str, int exit)
{
	printf("%s\n", str);
	return (exit);
}

void	ft_free_philos(t_data *data)
{
	unsigned int	i;
	if (!data)
		return (NULL);
	if (data->philos)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (data->philos[i]->sem_meal_name)
				free(data->philos[i]->sem_meal_name);
			free(data->philos[i]);
			i++;
		}
		free(data->philos);
	}
	if (data->pids)
		free(data->pids);
	free(data);
	return (NULL);
}

int	ft_free_data(char *str, t_data *data)
{
	if (data)
		ft_free_philos(data);
	return(ft_msg_err(str, 1));
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	// Encuentra el final de la cadena 'dest'
	i = 0;
	while (dest[i] != '\0')
		i++;

	// Copia la cadena 'src' al final de 'dest'
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	// Asegura que la cadena resultante esté terminada con '\0'
	dest[i] = '\0';

	return (dest);
}
