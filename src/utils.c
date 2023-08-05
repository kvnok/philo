/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 20:28:16 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/05 16:40:43 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//effects if allowed to print or not
bool check_status(t_philo p)
{
	bool check;
	pthread_mutex_lock(p.status_lock);
	check = *p.status;
	pthread_mutex_unlock(p.status_lock);
	
	//DEBUG THIS SCREWS WITH THINGS
	// pthread_mutex_lock(p.print_lock);
	// printf("P %d, ", p.id);
	// if (check == true)
	// 	printf("true\n");
	// else
	// 	printf("false\n");
	// pthread_mutex_unlock(p.print_lock);
	//DEBUG THIS SCREWS WITH THINGS
	return check;
}

bool check_if_ded(t_philo p, long long time)
{
	pthread_mutex_lock(p.print_lock);
	if ((cur_time(p) - time) > p.time_to_die)
	{
		if (check_status(p) == true)
		{
			pthread_mutex_lock(p.status_lock);
			printf("%lld %d died\n", time + p.time_to_die, p.id);
			*p.status = false;
			pthread_mutex_unlock(p.status_lock);
		}
		pthread_mutex_unlock(p.print_lock);
		return true;
	}
	pthread_mutex_unlock(p.print_lock);
	return false;
}
