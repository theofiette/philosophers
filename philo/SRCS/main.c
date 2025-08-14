/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:37:40 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/14 14:20:46 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
*	check the argument, if valid fill a stack struct.
*/
static int	parse(t_args *args, int argc, char **argv)
{
	if (check_usage(argc, argv) || check_values(argv))
		return (TRUE);
	fill_args(args, argc, argv);
	return (FALSE);
}

/*
* init the data (allocate and fill)
* check all functions that can fail
*/
static int	init(t_args *args, t_tabs *tabs, int *ready,
	pthread_mutex_t *ready_mutex)
{
	init_tabs(tabs);
	if (malloc_thread_tab(args, tabs)
		|| malloc_philo_tab(args, tabs)
		|| malloc_fork_tab(args, tabs)
		|| malloc_fork_state_tab(args, tabs)
		|| pthread_mutex_init(ready_mutex, NULL)
		|| fill_fork_tab(*args, *tabs))
		return (TRUE);
	fill_fork_state_tab(*args, *tabs);
	fill_philo_tab(*args, *tabs, ready, ready_mutex);
	return (FALSE);
}

static int	mutex_management(t_args *args, t_tabs *tabs, int *ready,
	pthread_mutex_t *ready_mutex)
{
	pthread_mutex_lock(ready_mutex);
	if (init_threads(args, tabs))
		return (TRUE);
	*ready = TRUE;
	pthread_mutex_unlock(ready_mutex);
	if (join_threads(args, *tabs))
		return (TRUE);
	pthread_mutex_destroy(ready_mutex);
	return (FALSE);
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
	if (parse(&args, argc, argv))
		return (0);
	if (init(&args, &tabs, &ready, &ready_mutex))
		return (1);
	if (mutex_management(&args, &tabs, &ready, &ready_mutex))
		return (2);
	clean(args, tabs);
	return (0);
}
