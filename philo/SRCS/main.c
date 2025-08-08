/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:37:40 by tfiette           #+#    #+#             */
/*   Updated: 2025/07/30 19:34:26 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	parse(t_args *args, int argc, char **argv)
{
	check_usage(argc, argv);
	check_values(argv);
	fill_args(args, argc, argv);
}

static void	init(t_args *args, t_tabs *tabs, int *ready,
	pthread_mutex_t *ready_mutex)
{
	init_tabs(tabs);
	malloc_thread_tab(args, tabs);
	malloc_philo_tab(args, tabs);
	malloc_fork_tab(args, tabs);
	malloc_fork_state_tab(args, tabs);
	pthread_mutex_init(ready_mutex, NULL);
	fill_fork_tab(*args, *tabs);
	fill_fork_state_tab(*args, *tabs);
	fill_philo_tab(*args, *tabs, ready, ready_mutex);
}

static void	mutex_management(t_args *args, t_tabs *tabs, int *ready,
	pthread_mutex_t *ready_mutex)
{
	pthread_mutex_lock(ready_mutex);
	init_threads(args, tabs);
	*ready = TRUE;
	pthread_mutex_unlock(ready_mutex);
	join_threads(args, *tabs);
	pthread_mutex_destroy(ready_mutex);
}

static void	clean(t_args args, t_tabs tabs)
{
	clean_mutexes(args, tabs);
	clean_mallocs(tabs);
}

int	main(int argc, char **argv)
{
	t_args			args;
	t_tabs			tabs;
	int				ready;
	pthread_mutex_t	ready_mutex;

	ready = FALSE;
	parse(&args, argc, argv);
	init(&args, &tabs, &ready, &ready_mutex);
	mutex_management(&args, &tabs, &ready, &ready_mutex);
	clean(args, tabs);
	return (0);
}

/*TODO : CLEAN EXIT IN THREAD*/
/*TODO : CLEAN EXIT IF INIT MUTEX FAIL*/