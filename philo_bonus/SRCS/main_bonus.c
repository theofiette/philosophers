/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:16:39 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/13 16:26:13 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	parse(t_args *args, int argc, char **argv)
{
	check_usage(argc, argv);
	check_values(argv);
	fill_args(args, argc, argv);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_init	init;
	t_philo	philo;

	parse(&args, argc, argv);
	init_data(&args, &init);
	fill_philo(&args, &init, &philo);
	fork_management(&args, &init, &philo);
	sem_post(init.sem_ready);
	wait_for_children(&args, &init);
	clean_init(&init);
	return (0);
}
