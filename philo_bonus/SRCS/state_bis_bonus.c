/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bis_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:31:13 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/13 16:31:22 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	_state_taking(t_philo *philo, suseconds_t time)
{
	state_print(time, philo);
	switch_state(philo, STATE_EATING, time);
}

void	_state_eating(t_philo *philo, suseconds_t time)
{
	if (time - philo->time_start_eat >= philo->time_to_eat)
	{
		philo->meal_done ++;
		if (philo->meal_nbr && philo->meal_done == philo->meal_nbr)
			switch_state(philo, STATE_STOP, time);
		else
			switch_state(philo, STATE_SLEEPING, time);
	}
	usleep(100);
}

void	_state_sleeping(t_philo *philo, suseconds_t time)
{
	if (philo->state == STATE_DYING)
		return ;
	if (time - philo->time_start_sleep >= philo->time_to_sleep)
	{
		switch_state(philo, STATE_THINKING, time);
	}
	usleep(100);
}

void	_state_thinking(t_philo *philo, suseconds_t time)
{
	if (philo->alone)
	{
		philo->state = STATE_TAKING;
		state_print(time, philo);
		usleep(philo->time_to_die * 1000);
		switch_state(philo, STATE_DYING, time);
	}
	else
	{
		if (philo->meal_done
			&& (philo->time_to_die <= philo->time_to_eat * (2 + philo->odd)))
		{
			usleep(100);
			return ;
		}
		sem_wait(philo->sem_forks);
		philo->forks ++;
		switch_state(philo, STATE_TAKING, time);
	}	
}
