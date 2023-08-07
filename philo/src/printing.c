/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 20:26:18 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/05 17:05:17 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_with_time(t_philo p, char *message)
{
	pthread_mutex_lock(p.print_lock);
	if (check_status(p) == true)
		printf("%lld %d %s\n", cur_time(p), p.id, message);
	pthread_mutex_unlock(p.print_lock);
}
