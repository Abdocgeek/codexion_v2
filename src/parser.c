/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 17:08:30 by abchahid          #+#    #+#             */
/*   Updated: 2026/08/17 18:55:49 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_valid_number(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (1);
		else
			i++;
	}
	return (0);
}

int	set_scheduler(char *str, t_scheduler *policy)
{
	if (strcmp(str, "edf") == 0)
		*policy = EDF;
	else if (strcmp(str, "fifo") == 0)
		*policy = FIFO;
	else
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_sim_args *args)
{
	int			i;

	if (argc != 9)
		return (1);
	i = 1;
	while (i <= 7)
	{
		if (!is_valid_number(argv[i]))
			return (1);
		i++;
	}
	if (!set_scheduler(argv[8], &args->scheduler))
		return (1);
	args->nb_coders = atoi(argv[1]);
	args->burnout_time = atoi(argv[2]);
	args->compile_time = atoi(argv[3]);
	args->debug_time = atoi(argv[4]);
	args->refactor_time = atoi(argv[5]);
	args->compiles_req = atoi(argv[6]);
	args->cooldown_time = atoi(argv[7]);
	return (0);
}
