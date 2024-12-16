/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:25:12 by marigome          #+#    #+#             */
/*   Updated: 2024/12/16 13:13:57 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	env;

	env.max_ate = 0;
	env.stopping = 0;
	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 2);
	if (!ft_check_args(&env, argc, argv))
		return (printf("Please, insert numbers\n\n"), 1);
	if (!ft_init_philo_sim(&env))
		return (printf("Error: Memory allocation failed\n"), 2);
	if (!ft_thread(&env))
		return (printf("Error: Thread creation failed\n"), 2);
	return (0);
}
