/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:20:04 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/10 13:48:18 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	print_error(char *err_str)
{
	int len;

	len = ft_strlen(err_str);
	write(2, err_str, len);
}

void	clean_init(t_init *init)
{
	int i;

	i = 0;
	if (init->pid_tab)
	{
		while (init->pid_tab[i])
		{
			if (waitpid(init->pid_tab[i], NULL, WNOHANG))
			{
				kill(init->pid_tab[i], SIGTERM);
				init->pid_tab[i] = 0;
			}
			kill(init->pid_tab[i], SIGTERM);
			init->pid_tab[i] = 0;
			i ++;
		}
		free(init->pid_tab);
	}
	if (init->sem_ready && init->sem_ready != SEM_FAILED)
	{
		sem_close(init->sem_ready);
	}
	if (init->sem_forks && init->sem_forks != SEM_FAILED)
	{
		sem_close(init->sem_forks);
	}
	if (init->sem_stop && init->sem_stop != SEM_FAILED)
	{
		sem_close(init->sem_stop);
	}
}

void	failure_exit(char *err_str, int err_status, t_init *init)
{
	print_error(err_str);
	clean_init(init);
	exit(err_status);
}