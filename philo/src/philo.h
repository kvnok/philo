/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kkroon <kkroon@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/25 16:50:33 by kkroon        #+#    #+#                 */
/*   Updated: 2023/08/07 14:15:18 by kkroon        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
has to be turned in philo directory
can not use libft
allowed functions :
	memset					:	set n bytes to char c
	printf					:	print in multiple formats
	malloc					:	allocate memory in bytes
	free					:	free allocated memory block
	write					:	output to fd or std
	usleep					:	suspend execution of calling a thread for microseconds
	gettimeofday			:	time since epoch
	pthread_create			:	creates new thread
	pthread_detach			:	mark as detach, free upon termination
	*FOR SYNCHRONIZATION*
	pthread_join			:	blocks calling thread until termination 
	pthread_mutex_init		:	create and init mutex object
	pthread_mutex_destroy	:	destroys object, freeing resources
	pthread_mutex_lock		:	create lock on mutex, blocking if used by other thread
	pthread_mutex_unlock	:	releases lock, can be used again by other threads
*/

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo
{
	pthread_t		thread;
	bool			limit_eating;
	int				amount_eaten;
	bool			done_eating;
	pthread_mutex_t	*amount_done_eating_lock;
	int				*amount_done_eating;
	int				id;
	int				nr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_to_eat;
	struct timeval	end;
	long long		start_sec;
	long long		start_usec;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*status_lock;
	bool			*status;
	pthread_mutex_t	*fork_flags_lock;
	bool			*left_flag;
	bool			*right_flag;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				nr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nr_to_eat;
	bool			limit_eating;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	status_lock;
	bool			status;
	pthread_mutex_t	amount_done_eating_lock;
	int				amount_done_eating;
	pthread_mutex_t	fork_flags_lock;
	bool			*forks_flags;
	struct timeval	start;
}	t_data;

//main.c
int			check_argv(char **argv);
int			fill_data(int argc, char **argv, t_data *d);
int			cleanup(t_data *d);

//yep_atoi.c
int			ft_isdigit(int c);
long long	yep_atoi(char *s);

//time_stuff.c
long long	cur_time(t_philo p);
void		proper_sleep(t_philo p, int time_to_sleep);

//thread_stuff.c
int			fill_philo(t_data *d);
int			post_mortem(t_data d, int flag);
int			threading(t_data d);

//routine.c
void		first_run_prio(int *flag, t_philo p);
void		*routine(void *arg);

//eating.c
bool		grab_left(t_philo p, long long time);
bool		grab_right(t_philo p, long long time);
void		drop_forks(t_philo p, bool left, bool right);
void		update_eat_stats(t_philo *p);
void		eating(t_philo *p, long long *time);

//printing.c
void		print_with_time(t_philo p, char *message);

//utils.c
bool		check_status(t_philo p);
bool		check_if_ded(t_philo p, long long time);
#endif
