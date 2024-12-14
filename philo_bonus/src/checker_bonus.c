/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:55:03 by marigome          #+#    #+#             */
/*   Updated: 2024/12/14 11:29:25 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_manage_err(const char *err)
{
	printf("Error: ""%s\n", err);
	exit (EXIT_FAILURE);
}

void	ft_manage_err_simple(const char *err)
{
	printf("Error: ""%s\n", err);
}

int	ft_is_int(char *nptr)
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
	while (nptr[i] != '\0' && (nptr[i] >= 48 && nptr[i] <= 57))
	{
		if (value > 214748364 || (value == 214748364
				&& ((!neg && nptr[i] - '0' > 7) || (neg && nptr[i] - '0' > 8))))
			return (0);
		else
			value = (value * 10) + nptr[i++] - '0';
	}
	return (1);
}

int	ft_check_params(t_envp *envp, int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!ft_isinteger(argv[i]))
		{
			printf("Argument:%i is not an integer" "\n", i);
			return (ft_manage_err_simple(NO_INT_ARGV_ERR), EXIT_FAILURE);
		}
		if (ft_philo_atoi(argv[i]) < 0)
		{
			printf("%i" "\n", i);
			return (ft_manage_err_simple(INT_NEG_ARGV_ERR), EXIT_FAILURE);
		}
		i++;
	}
	ft_init_struct(envp, argc, argv);
	if (envp->philo_eat_limit < 0 || envp->time_to_die < 0 || envp->\
	time_to_eat < 0 || envp->time_to_sleep < 0 || envp->nbr_philos < 1)
	{
		printf("Arguments invalid\n");
		return (ft_manage_err_simple(PARAMS_ERR), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

