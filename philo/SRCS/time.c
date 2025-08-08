/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:09:53 by tfiette           #+#    #+#             */
/*   Updated: 2025/07/30 19:15:50 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	synchronize(t_philo *philo)
{
	pthread_mutex_lock(philo->ready_mutex);
	pthread_mutex_unlock(philo->ready_mutex);
}

suseconds_t	get_time(struct timeval *time, suseconds_t start_time)
{
	suseconds_t	res_time;

	gettimeofday(time, NULL);
	res_time = (time->tv_sec * 1000) + (time->tv_usec / 1000);
	res_time -= start_time;
	return (res_time);
}

void	set_time(struct timeval *time, suseconds_t *start_time)
{
	gettimeofday(time, NULL);
	*start_time = (time->tv_sec * 1000) + (time->tv_usec / 1000);
}
