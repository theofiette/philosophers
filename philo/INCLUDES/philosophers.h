/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 12:06:54 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/08 10:50:36 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//// -headers

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

//// -macros

# define TRUE	1
# define FALSE	0

//// -enums

enum	e_state
{
	INIT,
	TAKING,
	EATING,
	SLEEPING,
	THINKING,
	DYING,
	STOP
};

enum	e_lock
{
	FREE,
	LOCKED
};

//// -typedefs

typedef struct s_args
{
	int	philo_nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meal_nbr;
	int	show;
}	t_args;

typedef struct s_philo
{
	int				id;
	int				odd;
	int				*ready;
	pthread_mutex_t	*ready_mutex;
	struct timeval	time;
	suseconds_t		start_time;
	int				state;
	pthread_mutex_t	*forks[2];
	int				*fork_state[2];
	int				fork_number;
	int				fork_first;
	int				fork_second;
	int				lock_first;
	int				lock_second;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_start_sleep;
	suseconds_t		time_to_sleep;
	suseconds_t		time_start_eat;
	suseconds_t		time_last_eat;
	suseconds_t		time_last_sleep;
	int				meal_nbr;
	int				meal_done;
	int				show;
	char			color[11];
}	t_philo;

typedef struct s_tabs
{
	pthread_t		*thread_tab;
	t_philo			*philo_tab;
	pthread_mutex_t	*fork_tab;
	int				*fork_state;
}	t_tabs;

//// -prototypes

//debug.c
void		debug_print_args(t_args *args);
//color.c
void		get_color(int color, t_philo *philo);
//failure.c 
void		clean_mutexes(t_args args, t_tabs tabs);
void		clean_n_mutexes(int n, t_tabs tabs);
void		clean_mallocs(t_tabs tabs);
void		failure_exit(char *err_str, int err_status, t_tabs tabs);
//parsing.c
void		check_values(char **argv);
void		check_usage(int argc, char **argv);
void		fill_args(t_args *args, int argc, char **argv);
//routine.c
void		*routine(void *arg);
//state.c
void		_state_machine(t_philo *philo, suseconds_t time);
void		switch_state(t_philo *philo, int new_state, suseconds_t time);
void		state_print(suseconds_t time, t_philo *philo);
void		_state_init(t_philo *philo, suseconds_t time);
void		_state_dying(t_philo *philo, suseconds_t time);
void		_state_taking(t_philo *philo, suseconds_t time);
void		_state_eating(t_philo *philo, suseconds_t time);
void		_state_sleeping(t_philo *philo, suseconds_t time);
void		_state_thinking(t_philo *philo, suseconds_t time);
//tab.c
void		init_tabs(t_tabs *tabs);
void		malloc_fork_tab(t_args *args, t_tabs *tabs);
void		malloc_philo_tab(t_args *args, t_tabs *tabs);
void		malloc_thread_tab(t_args *args, t_tabs *tabs);
void		malloc_fork_state_tab(t_args *args, t_tabs *tabs);
void		fill_fork_tab(t_args args, t_tabs tabs);
void		fill_fork_state_tab(t_args args, t_tabs tabs);
void		fill_philo_tab(t_args args, t_tabs tabs, int *init,
				pthread_mutex_t *mutex_ready);
//thread.c
void		init_threads(t_args *args, t_tabs *tabs);
void		join_threads(t_args *args, t_tabs tabs);
//time.c
void		synchronize(t_philo *philo);
suseconds_t	get_time(struct timeval *time, suseconds_t start_time);
void		set_time(struct timeval *time, suseconds_t *start_time);

//utils.c
int			ft_atoi(char *n);
int			ft_strlen(char *str);
int			ft_strcmp(char *str1, char *str2);
char		*ft_get_program_name(char *program);

#endif