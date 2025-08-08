/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:20:59 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/08 12:46:43 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	fill_fork_tab(t_args args, t_tabs tabs)
{
	int	i;

	i = 0;
	while (i < args.philo_nbr)
	{
		if (pthread_mutex_init(&tabs.fork_tab[i], NULL))
		{
			clean_n_mutexes(i, tabs);
			failure_exit("Failed to init forks mutexes", 1, tabs);
		}
		i ++;
	}
}

void	fill_fork_state_tab(t_args args, t_tabs tabs)
{
	int	i;

	i = 0;
	while (i < args.philo_nbr)
	{
		tabs.fork_state[i] = FREE;
		i ++;
	}
}

static void	link_forks(int i, t_args args, t_tabs tabs)
{
	if (i != args.philo_nbr - 1)
	{
		tabs.philo_tab[i].forks[1] = &tabs.fork_tab[i + 1];
		tabs.philo_tab[i].fork_state[1] = &tabs.fork_state[i + 1];
	}
	else
	{
		tabs.philo_tab[i].forks[1] = &tabs.fork_tab[0];
		tabs.philo_tab[i].fork_state[1] = &tabs.fork_state[0];
	}
	tabs.philo_tab[i].state = INIT;
}

void	fill_philo_tab(t_args args, t_tabs tabs, int *ready,
			pthread_mutex_t *ready_mutex)
{
	int	i;

	i = 0;
	while (i < args.philo_nbr)
	{
		tabs.philo_tab[i].id = i + 1;
		tabs.philo_tab[i].odd = args.philo_nbr % 2;
		tabs.philo_tab[i].ready = ready;
		tabs.philo_tab[i].ready_mutex = ready_mutex;
		tabs.philo_tab[i].time_to_die = (suseconds_t)args.time_to_die;
		tabs.philo_tab[i].time_to_eat = (suseconds_t)args.time_to_eat;
		tabs.philo_tab[i].time_to_sleep = (suseconds_t)args.time_to_sleep;
		tabs.philo_tab[i].meal_nbr = args.meal_nbr;
		get_color(i, &tabs.philo_tab[i]);
		tabs.philo_tab[i].show = args.show;
		tabs.philo_tab[i].fork_number = 0;
		tabs.philo_tab[i].forks[0] = &tabs.fork_tab[i];
		tabs.philo_tab[i].fork_state[0] = &tabs.fork_state[i];
		link_forks(i, args, tabs);
		i ++;
	}
}
