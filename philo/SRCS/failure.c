/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:15:00 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/14 12:50:49 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_mutexes(t_args args, t_tabs tabs)
{
	int	i;

	i = 0;
	while (i < args.philo_nbr)
	{
		pthread_mutex_destroy(&tabs.fork_tab[i]);
		i ++;
	}
}

void	clean_n_mutexes(int n, t_tabs tabs)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&tabs.fork_tab[i]);
		i ++;
	}
}

void	clean_mallocs(t_tabs tabs)
{
	if (tabs.thread_tab)
		free(tabs.thread_tab);
	if (tabs.philo_tab)
		free(tabs.philo_tab);
	if (tabs.fork_tab)
		free(tabs.fork_tab);
	if (tabs.fork_state)
		free(tabs.fork_state);
}

void	print_error(char *err_str)
{
	int		len;

	len = ft_strlen(err_str);
	write(2, err_str, len);
}

void	failure_exit(char *err_str, t_tabs tabs)
{
	print_error(err_str);
	clean_mallocs(tabs);
}
