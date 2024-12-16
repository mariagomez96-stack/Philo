/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 11:25:12 by marigome          #+#    #+#             */
/*   Updated: 2024/12/16 13:10:46 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"



int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc < 5 || argc > 6)
		return (ft_msg_err("Error: Wrong number of arguments", 1));
	if (!ft_check_args(data, argc, argv))
		return (ft_msg_err("Please, insert numbers\n\n", 1));
		

}

