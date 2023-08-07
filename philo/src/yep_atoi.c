/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   yep_atoi.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 11:26:48 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/06 15:44:13 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long	yep_atoi(char *s)
{
	long long	num;
	int			i;

	num = 0;
	i = 0;
	while (s[i])
	{
		num = num * 10;
		num = num + (s[i] - 48);
		if (num > INT_MAX)
			return (-1);
		i++;
	}
	return (num);
}
