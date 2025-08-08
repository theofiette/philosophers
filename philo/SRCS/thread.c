/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:16:42 by tfiette           #+#    #+#             */
/*   Updated: 2025/07/30 19:15:05 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_threads(t_args *args, t_tabs *tabs)
{
	int	i;

	i = 0;
	while (i < args->philo_nbr)
	{
		if (pthread_create(tabs->thread_tab + i, NULL,
				&routine, (void *)(tabs->philo_tab + i)))
			failure_exit("Failed to create threads\n", 1, *tabs);
		i ++;
	}
}

void	join_threads(t_args *args, t_tabs tabs)
{
	int	i;

	i = 0;
	while (i < args->philo_nbr)
	{
		if (pthread_join(tabs.thread_tab[i], NULL))
			failure_exit("Failed to join threads\n", 1, tabs);
		i ++;
	}
}
