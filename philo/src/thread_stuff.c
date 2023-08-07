/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread_stuff.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/31 16:50:43 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/07 14:17:26 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//norm be like this sometimes
int	fill_helper(t_data *d, int i)
{
	d->philos[i].limit_eating = d->limit_eating;
	d->philos[i].amount_eaten = 0;
	d->philos[i].done_eating = false;
	d->philos[i].amount_done_eating_lock = &d->amount_done_eating_lock;
	d->philos[i].amount_done_eating = &d->amount_done_eating;
	d->philos[i].id = i + 1;
	d->philos[i].nr_of_philos = d->nr_of_philos;
	d->philos[i].time_to_die = d->time_to_die;
	d->philos[i].time_to_eat = d->time_to_eat;
	d->philos[i].time_to_sleep = d->time_to_sleep;
	d->philos[i].nr_to_eat = d->nr_to_eat;
	d->philos[i].start_sec = d->start.tv_sec;
	d->philos[i].start_usec = d->start.tv_usec;
	d->philos[i].left = &d->forks[i];
	d->philos[i].right = &d->forks[(i + 1) % d->nr_of_philos];
	d->philos[i].print_lock = &d->print_lock;
	d->philos[i].status_lock = &d->status_lock;
	d->philos[i].status = &d->status;
	d->philos[i].fork_flags_lock = &d->fork_flags_lock;
	d->philos[i].left_flag = &d->forks_flags[i];
	d->philos[i].right_flag = &d->forks_flags[(i + 1) % d->nr_of_philos];
	return (0);
}

int	fill_philo(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nr_of_philos)
	{
		fill_helper(d, i);
		i++;
	}
	return (0);
}

int	post_mortem(t_data d, int flag)
{
	int	i;

	i = 0;
	while (i < d.nr_of_philos)
	{
		if (pthread_join(d.philos[i].thread, NULL) != 0)
			break;
		i++;
	}
	i = 0;
	while (i < d.nr_of_philos)
	{
		if (pthread_mutex_destroy(&d.forks[i]) != 0)
			break;
		i++;
	}
	if (flag >= 1)
		pthread_mutex_destroy(&d.print_lock);
	if (flag >= 2)
		pthread_mutex_destroy(&d.status_lock);
	if (flag >= 3)
		pthread_mutex_destroy(&d.fork_flags_lock);
	if (flag >= 4)
		pthread_mutex_destroy(&d.amount_done_eating_lock);
	return (1);
}

int	init_mutexes(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->nr_of_philos)
	{
		d->forks_flags[i] = true;
		if (pthread_mutex_init(&d->forks[i], NULL) != 0)
			return (post_mortem(*d, 0));
		i++;
	}
	if (pthread_mutex_init(&d->print_lock, NULL) != 0)
		return (post_mortem(*d, 1));
	if (pthread_mutex_init(&d->status_lock, NULL) != 0)
		return (post_mortem(*d, 2));
	if (pthread_mutex_init(&d->fork_flags_lock, NULL) != 0)
		return (post_mortem(*d, 3));
	if (pthread_mutex_init(&d->amount_done_eating_lock, NULL) != 0)
		return (post_mortem(*d, 4));
	return (0);
}

//probally want to clean this up / split up
//LEAN and MEAN
int	threading(t_data d)
{
	int	i;

	if (init_mutexes(&d) == 1)
		return (1);
	d.status = true;
	gettimeofday(&d.start, NULL);
	fill_philo(&d);
	i = 0;
	while (i < d.nr_of_philos)
	{
		if (pthread_create(&d.philos[i].thread, NULL,
				routine, &d.philos[i]) != 0)
			return (post_mortem(d, 4));
		i++;
	}
	post_mortem(d, 4);
	return (0);
}
