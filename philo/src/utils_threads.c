/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:02:17 by marigome          #+#    #+#             */
/*   Updated: 2024/12/20 19:04:55 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int ft_lock_stop_flag(t_data *data)
{
    int stop_flag;
    pthread_mutex_lock(&data->stopping_mutex);
    stop_flag = data->stopping;
    pthread_mutex_unlock(&data->stopping_mutex);
    return(stop_flag);
}