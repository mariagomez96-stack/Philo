/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:25:12 by marigome          #+#    #+#             */
/*   Updated: 2024/12/21 10:18:52 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_data	env;
	t_philo	*philo;

	if (argc < 5 || argc > 6)
		return (printf("Error: Wrong number of arguments\n"), 1);
	if (!ft_check_args(&env, argc, argv))
		return (printf("Please, insert right arguments\n\n"), 1);
	philo = ft_init_philo(&env);
	ft_init_simulation(&env, philo);
	sem_wait(env.stop);
	ft_destroy_all(&env, philo);
}
