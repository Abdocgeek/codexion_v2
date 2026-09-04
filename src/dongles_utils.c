/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 09:12:03 by abchahid          #+#    #+#             */
/*   Updated: 2026/09/04 10:37:22 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	wait_for_cooldown(t_dongle *dongle, t_data *data)
{
	long long	current_time;

	while (is_simulation_running(data))
	{
		pthread_mutex_lock(&dongle->lock);
		current_time = get_current_time_ms();
		if ((current_time - dongle->last_released_time) >= data->args.cooldown_time)
		{
			pthread_mutex_unlock(&dongle->lock);
			break ;
		}
		pthread_mutex_unlock(&dongle->lock);
		usleep(500);
	}
}


bool	grab_first(t_coder *coder, t_dongle *first)
{
	wait_for_cooldown(first, coder->data);
	if (!is_simulation_running(coder->data))
		return (false);
	enqueue_coder(coder, first);
	first->is_available = false;
	print_action(coder, "has taken a dongle");
	return (true);
}