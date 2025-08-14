/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:12:56 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/14 12:51:22 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_tabs(t_tabs *tabs)
{
	tabs->thread_tab = NULL;
	tabs->philo_tab = NULL;
	tabs->fork_tab = NULL;
	tabs->fork_state = NULL;
}

int	malloc_fork_tab(t_args *args, t_tabs *tabs)
{
	tabs->fork_tab = malloc(sizeof(pthread_mutex_t) * args->philo_nbr);
	if (tabs->fork_tab == NULL)
	{
		failure_exit("Failed to malloc forks\n", *tabs);
		return (TRUE);
	}
	return (FALSE);
}

int	malloc_fork_state_tab(t_args *args, t_tabs *tabs)
{
	tabs->fork_state = malloc(sizeof(pthread_mutex_t) * args->philo_nbr);
	if (tabs->fork_state == NULL)
	{
		failure_exit("Failed to malloc forks\n", *tabs);
		return (TRUE);
	}
	return (FALSE);
}

int	malloc_philo_tab(t_args *args, t_tabs *tabs)
{
	tabs->philo_tab = malloc(sizeof(t_philo) * args->philo_nbr);
	if (tabs->philo_tab == NULL)
	{
		failure_exit("Failed to malloc philosophers\n", *tabs);
		return (TRUE);
	}
	return (FALSE);
}

int	malloc_thread_tab(t_args *args, t_tabs *tabs)
{
	tabs->thread_tab = malloc(sizeof(pthread_t) * args->philo_nbr);
	if (tabs->thread_tab == NULL)
	{
		failure_exit("Failed to malloc threads\n", *tabs);
		return (TRUE);
	}
	return (FALSE);
}
