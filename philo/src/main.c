/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 16:50:25 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/07 14:12:08 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv(char **argv)
{
	int	i;
	int	x;

	i = 1;
	x = 0;
	while (argv[i] != NULL)
	{
		x = 0;
		while (argv[i][x])
		{
			if (ft_isdigit(argv[i][x]) == 0)
				return (1);
			x++;
		}
		i++;
	}
	return (0);
}

int	fill_data(int argc, char **argv, t_data *d)
{
	if (argc < 5 || argc > 6)
		return (1);
	if (check_argv(argv) == 1)
		return (1);
	d->limit_eating = false;
	d->nr_to_eat = INT_MAX;
	d->nr_of_philos = yep_atoi(argv[1]);
	d->time_to_die = yep_atoi(argv[2]);
	d->time_to_eat = yep_atoi(argv[3]);
	d->time_to_sleep = yep_atoi(argv[4]);
	if (argc == 6)
	{
		d->limit_eating = true;
		d->nr_to_eat = yep_atoi(argv[5]);
	}
	if (d->nr_of_philos <= 0 || d->nr_of_philos > 200)
		return (1);
	if (d->time_to_die <= 0 || d->time_to_eat < 0
		|| d->time_to_sleep < 0 || d->nr_to_eat <= 0)
		return (1);
	return (0);
}

int	cleanup(t_data *d)
{
	free(d->philos);
	free(d->forks);
	free(d->forks_flags);
	return (1);
}

/*
argv[0] : ./philo
argv[1] : number_of_philosophers
argv[2] : time_to_die
argv[3] : time_to_eat
argv[4] : time_to_sleep
argv[5] : number_of_times_each_philosopher_must_eat
*/
int	main(int argc, char **argv)
{
	t_data	d;

	if (fill_data(argc, argv, &d) == 1)
	{
		printf("incorrect input\n");
		return (1);
	}
	d.philos = NULL;
	d.forks = NULL;
	d.forks_flags = NULL;
	d.philos = malloc(d.nr_of_philos * sizeof(t_philo));
	if (d.philos == NULL)
		return (1);
	d.forks = malloc(d.nr_of_philos * sizeof(pthread_mutex_t));
	if (d.forks == NULL)
		return (cleanup(&d));
	d.forks_flags = malloc(d.nr_of_philos * sizeof(bool));
	if (d.forks_flags == NULL)
		return (cleanup(&d));
	threading(d);
	cleanup(&d);
	return (0);
}
