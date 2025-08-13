/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:06:36 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/13 13:07:17 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	synchronize(t_init *init, t_philo *philo)
{
	suseconds_t time;

	sem_wait(init->sem_ready);
	sem_post(init->sem_ready);
	set_time(&philo->time, &philo->start_time);
	time = get_time(&philo->time, philo->start_time);
	philo->time_start_eat = time;
	philo->time_start_sleep = time;
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