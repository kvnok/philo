/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eating.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/04 20:49:05 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/05 17:01:57 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	grab_left(t_philo p, long long time)
{
	bool	flag;

	while (check_if_ded(p, time) == false)
	{
		pthread_mutex_lock(p.fork_flags_lock);
		flag = *p.left_flag;
		if (flag == true)
		{
			pthread_mutex_lock(p.left);
			print_with_time(p, "has taken a fork");
			*p.left_flag = false;
			pthread_mutex_unlock(p.fork_flags_lock);
			return (true);
		}
		pthread_mutex_unlock(p.fork_flags_lock);
	}
	return (false);
}

bool	grab_right(t_philo p, long long time)
{
	bool	flag;

	while (check_if_ded(p, time) == false)
	{
		pthread_mutex_lock(p.fork_flags_lock);
		flag = *p.right_flag;
		if (flag == true)
		{
			pthread_mutex_lock(p.right);
			print_with_time(p, "has taken a fork");
			*p.right_flag = false;
			pthread_mutex_unlock(p.fork_flags_lock);
			return (true);
		}
		pthread_mutex_unlock(p.fork_flags_lock);
	}
	return (false);
}

void	drop_forks(t_philo p, bool left, bool right)
{
	pthread_mutex_lock(p.fork_flags_lock);
	*p.left_flag = true;
	*p.right_flag = true;
	pthread_mutex_unlock(p.fork_flags_lock);
	if (left == true)
		pthread_mutex_unlock(p.left);
	if (right == true)
		pthread_mutex_unlock(p.right);
}

//check if there is a limit
//update how often this philo has eaten
//set done_eating to true when nr_to_eat is reached
//also increment the amount_done_eating from data
//if every philo is done eating, set status to false
void	update_eat_stats(t_philo *p)
{
	if (p->limit_eating == true)
	{
		p->amount_eaten = p->amount_eaten + 1;
		if (p->amount_eaten == p->nr_to_eat)
		{
			p->done_eating = true;
			pthread_mutex_lock(p->amount_done_eating_lock);
			*p->amount_done_eating = *p->amount_done_eating + 1;
			pthread_mutex_unlock(p->amount_done_eating_lock);
		}
		if (p->done_eating == true)
		{
			pthread_mutex_lock(p->amount_done_eating_lock);
			if (*p->amount_done_eating == p->nr_of_philos)
			{
				pthread_mutex_lock(p->status_lock);
				*p->status = false;
				pthread_mutex_unlock(p->status_lock);
			}
			pthread_mutex_unlock(p->amount_done_eating_lock);
		}
	}
}

void	eating(t_philo *p, long long *time)
{
	bool	left;
	bool	right;

	left = grab_left(*p, *time);
	right = grab_right(*p, *time);
	print_with_time(*p, "is eating");
	*time = cur_time(*p);
	proper_sleep(*p, p->time_to_eat);
	if (left == true && right == true)
		update_eat_stats(p);
	drop_forks(*p, left, right);
}
