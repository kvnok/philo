/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printing.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 20:26:18 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/04 20:32:14 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void debug_print(t_philo p, long long time)
{
	//DEBUG THIS SCREWS WITH THINGS
	pthread_mutex_lock(p.print_lock);
	printf("\nDEBUGGING %d\n", p.id);
	printf("cur time\t\t%lld\n", cur_time(p));
	printf("last ate\t\t%lld\n", time);
	printf("allowed time\t\t%d\n", p.time_to_die);
	printf("time since last meal\t%lld\n", (cur_time(p) - time));
	printf("allowed - last ate\t%lld\n", (p.time_to_die - (cur_time(p) - time)));
	printf("DEBUGGING %d\n\n", p.id);
	pthread_mutex_unlock(p.print_lock);
	//DEBUG THIS SCREWS WITH THINGS
}

void print_with_time(t_philo p, char *message)
{
	//maybe need to do outside
	pthread_mutex_lock(p.print_lock);
	if (check_status(p) == true)
		printf("%lld %d %s\n", cur_time(p), p.id, message);
	pthread_mutex_unlock(p.print_lock);
}
