/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 18:08:24 by abchahid          #+#    #+#             */
/*   Updated: 2026/09/04 08:05:52 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


static void	wait_for_start_signal(t_data *data)
{
	pthread_mutex_lock(&data->sim_start_lock);
	while (!data->sim_running)
	{
		pthread_cond_wait(&data->sim_start_cond, &data->sim_start_lock);
	}
	pthread_mutex_unlock(&data->sim_start_lock);
}

void	*coder_routine(void *arg)
{
	t_coder		*coder;

	coder = (t_coder *)arg;
	wait_for_start_signal(coder->data);
	while (is_simulation_running(coder->data))
	{
		if (take_dongles(coder))
		{
			do_compile(coder);
			drop_dongles(coder);
			do_debug(coder);
			do_refactor(coder);
		}
		if (coder->compiles_done == coder->data->args.compiles_req)
			break ;
	}
	return (NULL);
}