/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_env_structs_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:08:19 by marigome          #+#    #+#             */
/*   Updated: 2024/12/16 14:03:54 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	ft_getlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

// INIT PHILOS //

static char *ft_name_sem(char *str, unsigned int id)
{
    unsigned int	i;
	unsigned int	digit_count;
	char			*sem_name;
	char			*tmp;

	// Calcular la cantidad de dígitos en el ID
	i = id;
    digit_count = ft_getlen(i);

	// Calcular la longitud total del nombre del semáforo
	i = ft_strlen(str) + digit_count;

	// Reservar memoria para el nombre del semáforo
	sem_name = malloc(sizeof * sem_name * (i + 1));
	if (sem_name == NULL)
		return (NULL);

	// Inicializar el nombre del semáforo con una cadena vacía
	sem_name[0] = '\0';

	// Concatenar el prefijo del nombre del semáforo
	sem_name = ft_strcat(sem_name, str);

	// Convertir el ID a una cadena de texto y concatenarlo al nombre
	tmp = ft_utoa(id, digit_count);
	sem_name = ft_strcat(sem_name, tmp);

	// Liberar la memoria temporal usada para el ID convertido
	free(tmp);

	return (sem_name);
}

static bool ft_complete_philo_sem_names(t_philo *philo)
{
	philo->sem_meal_name = set_name_sem("Philo_meal", philo->id + 1);
	if (philo->sem_meal_name == NULL)
		return (false);
	return (true);
}

static t_philo **ft_complete_philo_arr(t_philo **philos, t_data *data)
{
    int i;

    i = 0;
    while (i < data->philo_count)
    {
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
            return (ft_free_data(STR_ERR_MALLOC, data), 0);
        philos[i]->table = data;
        philos[i]->id = i;
        if (!ft_complete_philo_sem_names(philos[i]))
            return (ft_free_data(STR_ERR_THREAD, data), 0);
        philos[i]->times_ate = 0;
        philos[i]->nb_forks_held = 0;
        philos[i]->ate_enough = 0;
        i++;
    }
    return (philos);
}


t_philo **ft_init_philos(t_data * data)
{
    t_philo **philos;

    philos = malloc(sizeof(t_philo *) * data->philo_count + 1);
    philos = ft_complete_philo_arr(philos, data);
}

// INIT SEMAPHORES //

static bool	init_global_semaphores(t_data *table)
{
	unlink_global_sems();
	table->sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT,
			S_IRUSR | S_IWUSR, table->philo_count);
	if (table->sem_forks == SEM_FAILED)
		return (sem_error_cleanup(table));
	table->sem_write = sem_open(SEM_NAME_WRITE, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (table->sem_write == SEM_FAILED)
		return (sem_error_cleanup(table));
	table->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, table->philo_count);
	if (table->sem_philo_full == SEM_FAILED)
		return (sem_error_cleanup(table));
	table->sem_philo_dead = sem_open(SEM_NAME_DEAD, O_CREAT,
			S_IRUSR | S_IWUSR, table->philo_count);
	if (table->sem_philo_dead == SEM_FAILED)
		return (sem_error_cleanup(table));
	table->sem_stop = sem_open(SEM_NAME_STOP, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (table->sem_stop == SEM_FAILED)
		return (sem_error_cleanup(table));
	return (true);
}

// INIT DATA //

t_data	*init_table(int ac, char **av, int i)
{
	t_data	*table;

	table = malloc(sizeof(t_data));
	if (!table)
		return (error_null(STR_ERR_MALLOC, NULL, 0));
	table->philo_count = integer_atoi(av[i++]);
	table->time_to_die = integer_atoi(av[i++]);
	table->time_to_eat = integer_atoi(av[i++]);
	table->time_to_sleep = integer_atoi(av[i++]);
	table->must_eat_count = -1;
	table->philo_full_count = 0;
	table->stop_sim = false;
	if (ac - 1 == 5)
		table->must_eat_count = integer_atoi(av[i]);
	if (!init_global_semaphores(table))
		return (NULL);
	table->philos = init_philosophers(table);
	if (!table->philos)
		return (NULL);
	table->pids = malloc(sizeof * table->pids * table->philo_count);
	if (!table->pids)
		return (ft_free_data(STR_ERR_MALLOC, 0));
	return (table);
}