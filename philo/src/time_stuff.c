/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_stuff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 16:47:00 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/06 16:06:20 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//time since start of execution
//usec has to be divided by 1000 to move comma over by 3 spots
long long	cur_time(t_philo p)
{
	long long	seconds;
	long long	milliseconds;

	gettimeofday(&p.end, NULL);
	seconds = (p.end.tv_sec - p.start_sec) * 1000;
	milliseconds = (p.end.tv_usec - p.start_usec) / 1000;
	return (seconds + milliseconds);
}

//keep waiting half a millisecond, 500 microseconds
//until time_to_sleep amount in the future is reached
void	proper_sleep(t_philo p, int time_to_sleep)
{
	long long	goal;

	if (check_status(p) == false)
		return ;
	goal = cur_time(p) + time_to_sleep;
	while (cur_time(p) < goal)
	{
		if (check_status(p) == false)
			return ;
		usleep(500);
	}
}
