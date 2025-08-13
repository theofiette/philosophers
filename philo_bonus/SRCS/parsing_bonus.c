/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:24:11 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/13 16:28:58 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
*	iterate through argv to make sure all args are digits and between 0 to INT_MAX
*/
void	check_values(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && i < 6)
	{
		if (!is_digits(argv[i]) || !is_pos_int(argv[i]))
		{
			printf("%s: \e[1mInvalid format.\e[0m", ft_get_program_name(argv[0]));
			printf("\nUse --usage for more info.\n");
			exit(1);
		}
		i ++;
	}
}

/*
*	iterate throught argv to :
*	- look for commands
*	- ensure usage is correct (number of args)
*/
void	check_usage(int argc, char **argv)
{
	if (argc >= 2 && !(ft_strcmp(argv[1], "--usage")))
	{
		printf("\n%s: Usage:", ft_get_program_name(argv[0]));
		printf("\e[93;4m\targ 1\e[39;0m : number of philosphers.\e\n");
		printf("\e[93;4m\t\t\targ 2\e[39;0m : time to die (in ms).\n");
		printf("\e[93;4m\t\t\targ 3\e[39;0m : time to eat (in ms).\n");
		printf("\e[93;4m\t\t\targ 4\e[39;0m : time to sleep (in ms).\n");
		printf("\e[90;4m\t\t\targ 5\e[0m : nbr of meals needed. (opt)\e[39m\n");
		printf("\e[90;4m\t\t\targ 6\e[0m : -s to show meal nbr. (opt)\e[39m\n");
		printf("\e[1m\nAll args must be numbers between 1 and INT_MAX.\n\n");
		exit(1);
	}
	if (argc < 5 || (argc > 6 && (ft_strcmp(argv[6], "-s"))) || argc > 7)
	{
		printf("%s: Use --usage for more info.\n", ft_get_program_name(argv[0]));
		exit(1);
	}
}

/*
*	fills args with int values 
*	cast the struct as an int_tab and iterate
*/
void	fill_args(t_args *args, int argc, char **argv)
{
	int	i;

	i = 0;
	args->meal_nbr = 0;
	args->show = FALSE;
	while (++i < argc)
		((int *)args)[i - 1] = ft_atoi(argv[i]);
	if (argc == 7)
		args->show = TRUE;
}
