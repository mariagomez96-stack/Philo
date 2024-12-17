/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:05:23 by marigome          #+#    #+#             */
/*   Updated: 2024/12/17 13:16:57 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	ft_error_put(t_data*simulation, char *message, int ret)
{
	if (simulation)
	{
		if (simulation->forks)
			free(simulation->forks);
	}
	printf("%s\n", message);
	return (ret);
}

int	ft_is_int(char *arg)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			num = num * 10 + (arg[i] - '0');
		else
			return (ft_error_put(NULL, "Error: Number Only", -1));
		i++;
	}
	return (num);
}

/*int	ft_set_rest(t_data *simulation, char **argv, int i)
{
	simulation->time_to_sleep = ft_atoi(argv);
	if (i == 5)
	{
		if (argv[5] == 0)
			simulation->eat_counter = -1;
		else
		{
			simulation->eat_counter = ft_atoi(argv[5]);
			simulation->current_eat = 0;
			simulation->max_eat = simulation->eat_counter * simulation->philo_count;
		}
	}
	return (0);
}

int	ft_set_data(t_data *simulation, char **argv, int i)
{
	if (i == 1)
	{
		if (argv[0] == '0')
			return (ft_error_put(NULL, "Error: NO PHELOSOPHER IN THE TABILE", 1));
		simulation->philo_count = ft_atoi(argv[1]);
	}
	else if (i == 2)
		simulation->time_to_die = ft_atoi(argv[2]);
	else if (i == 3)
		simulation->time_to_eat = ft_atoi(argv[3]);
	else if (i == 4)
		simulation->time_to_sleep = ft_atoi(argv[4]);
	else if (i == 5)
	{
		if (argv[5] == '0')
			simulation->eat_counter = -1;
		else
		{
			simulation->eat_counter = ft_atoi(argv[5]);
			simulation->current_eat = 0;
			simulation->max_eat = simulation->eat_counter * simulation->philo_count;
		}
	}
	else
		ft_set_rest(simulation, argv, i);
	return (0);
}

int	ft_parsing(char **av, t_data *simulation)
{
	int				num;
	int				i;

	i = 1;
	while (av[i])
	{
		num = ft_is_int(av[i]);
		if (num == -1)
			return (1);
		if (ft_set_data(simulation, av, i))
			return (1);
		i++;
	}
	if (i == 5)
	{
		simulation->eat_counter = -1;
		simulation->current_eat = -1;
		simulation->max_eat = -1;
	}
	return (0);
}*/


int	ft_check_args(t_data *env, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_is_int(argv[i]))
			return (printf("Error: Argument %i is not an integer\n", i), 0);
		if (ft_atoi(argv[i]) < 0)
			return (printf("Error: Argument %i is negative\n", i), 0);
		i++;
	}
	ft_init_env(argc, argv, env);
	if (env->philo_count < 1 || env->time_to_die < 0 || env->time_to_eat < 0
		|| env->time_to_sleep < 0)
		return (printf("Error: Arguments must be greater than 0\n"), 0);
	return (1);
}