/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:34:39 by abchahid          #+#    #+#             */
/*   Updated: 2026/08/18 19:04:25 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "codexion.h"

void	start_simulation(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->args.nb_coders)
	{
		pthread
	}
}

bool	is_simulation_running(t_data *data)
{
	bool	is_running;

	pthread_mutex_lock(&data->state_lock);
	is_running = &data->is_running;
	pthread_mutex_unlock(&data->state_lock);
	return is_running;
}
