/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 10:40:37 by abchahid          #+#    #+#             */
/*   Updated: 2026/08/18 18:54:31 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static bool	init_coders(t_data *data)
{
	int		i;

	data->coders = (t_coder *)malloc(sizeof(t_coder) * data->args.nb_coders);
	if (!data->coders)
		return (false);
	i = 0;
	while (i < data->args.nb_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].last_compiled = 0;
		i++;
	}
	return (true);
}

static bool	init_dongles(t_data *data)
{
	int		i;

	data->dongles = (t_dongle *)malloc(sizeof(t_dongle) * data->args.nb_coders);
	if (!data->dongles)
		return (false);
	i = 0;
	while (i < data->args.nb_coders)
	{
		data->dongles[i].id = i;
		data->dongles[i].last_released = 0;
		if (!pqueue_create(&data->dongles[i].pqueue))
			return (false);
		if (!pthread_mutex_init(&data->dongles[i].lock, NULL))
			return (false);
	}
	return (true);
}

bool	init_data(t_data *data)
{
	if(!init_coders(data))
		return (false);
	if (!init_dongles(data))
		return (false);
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->sim_start_lock, NULL);
	pthread_cond_init(&data->sim_start_cond, NULL);
}

bool	free_all(t_data *data)
{
	int		i;

	i = 0;
	if (data->coders)
		free(data->coders);
	if (data->dongles)
	{
		while (i <= data->args.nb_coders)
		{
			free(data->dongles[i].pqueue.requests);
			pthread_mutex_destroy(&data->dongles[i].lock);
			i++;
		}
		free(data->dongles);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_cond_destroy(&data->sim_start_cond);
}
