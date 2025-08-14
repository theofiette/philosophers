/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:16:42 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/14 14:20:58 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads(t_args *args, t_tabs *tabs)
{
	int	i;

	i = 0;
	while (i < args->philo_nbr)
	{
		if (pthread_create(tabs->thread_tab + i, NULL,
				&routine, (int *)(tabs->philo_tab + i)))
		{
			failure_exit("Failed to create threads\n", *tabs);
			return (TRUE);
		}
		i ++;
	}
	return (FALSE);
}

int	join_threads(t_args *args, t_tabs tabs)
{
	int	i;

	i = 0;
	while (i < args->philo_nbr)
	{
		if (pthread_join(tabs.thread_tab[i], NULL))
		{
			failure_exit("Failed to join threads\n", tabs);
			return (TRUE);
		}
		i ++;
	}
	return (FALSE);
}
