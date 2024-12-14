/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:25:12 by marigome          #+#    #+#             */
/*   Updated: 2024/12/14 11:40:10 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char *argv[])
{
	t_envp	envp;

	envp.eat_max = 0;
	envp.stopping_rule = 0;
	if (argc < 5 || argc > 6)
	{
		ft_manage_err_simple(NUM_ARGV_ERR);
		return (ft_manage_err_simple(USAGE_ERR), EXIT_FAILURE);
	}
	if (ft_check_params(&envp, argc, argv))
		return (ft_manage_err_simple(BYE), EXIT_FAILURE);
	if (ft_init_sim(&envp))
		return (ft_manage_err_simple(INIT_ERR), EXIT_FAILURE);
	if (ft_create_threads_and_monitor(&envp))
		return (ft_manage_err_simple(THREADS_ERR), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

