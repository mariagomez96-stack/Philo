/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:58:10 by marigome          #+#    #+#             */
/*   Updated: 2024/12/14 11:33:45 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_philo_atoi(const char *nptr)
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
	while (nptr[i] != '\0' && nptr[i] >= 48 && nptr[i] <= 57)
	{
		if (value >= 922337203685477580 || (value == 922337203685477580
				&& ((!neg && nptr[i] - '0' > 7) || (neg && nptr[i] - '0' > 8))))
			return (-1 * !neg);
		else
			value = (value * 10) + nptr[i++] - '0';
	}
	if (neg)
		value = -value;
	return (value);
}

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_rev_str(char *str)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = ft_strlen(str) - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

static int	ft_getlen(int n)
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

char	*ft_philo_itoa(int n)
{
	char			*ret;
	int				i;
	unsigned int	tmp_nbr;

	i = 0;
	ret = malloc(sizeof(*ret) * (ft_getlen(n) + 1));
	if (!ret)
		return (NULL);
	if (n < 0)
		tmp_nbr = -1 * n;
	else
		tmp_nbr = n;
	while (tmp_nbr != 0)
	{
		ret[i++] = (tmp_nbr % 10) + '0';
		tmp_nbr /= 10;
	}
	if (n == 0)
		ret[i++] = '0';
	if (n < 0)
		ret[i++] = '-';
	ret[i] = '\0';
	ft_rev_str(ret);
	return (ret);
}
