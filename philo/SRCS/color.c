/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 19:01:20 by tfiette           #+#    #+#             */
/*   Updated: 2025/07/30 19:10:51 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_color(int color, t_philo *philo)
{
	int	i;

	i = 7;
	philo->color[0] = '\e';
	philo->color[1] = '[';
	philo->color[2] = '3';
	philo->color[3] = '8';
	philo->color[4] = ';';
	philo->color[5] = '5';
	philo->color[6] = ';';
	philo->color[7] = '0';
	philo->color[8] = '0';
	philo->color[9] = '0';
	color = (color % 230) + 1;
	if (color >= 100)
		philo->color[i] = '0' + (color / 100);
	i ++;
	color = color % 100;
	if (color >= 10)
		philo->color[i] = '0' + (color / 10);
	i ++;
	color = color % 10;
	philo->color[i++] = '0' + color;
	philo->color[i++] = 'm';
	philo->color[i++] = '\0';
}
