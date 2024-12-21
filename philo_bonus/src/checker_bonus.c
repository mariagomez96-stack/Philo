/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:05:23 by marigome          #+#    #+#             */
/*   Updated: 2024/12/21 10:18:55 by marigome         ###   ########.fr       */
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
