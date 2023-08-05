/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 20:32:31 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/05 15:59:07 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void first_run_prio(int *flag, t_philo p)
{
	if (p.id % 2 == 1 && *flag == 0)
	{
		print_with_time(p, "is thinking");
		proper_sleep(p, (p.time_to_eat / 2));
		*flag = 1;
	}
}

void *routine(void *arg)
{
	t_philo		p;
	int			flag;
	long long	time;

	p = *(t_philo *)arg;
	flag = 0;
	time = cur_time(p);
	while(check_status(p) == true)
	{
		first_run_prio(&flag, p);
		eating(&p, &time);
		print_with_time(p, "is sleeping");
		proper_sleep(p, p.time_to_sleep);
		print_with_time(p, "is thinking");
	}
	return NULL;
}
