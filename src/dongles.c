/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 08:50:51 by abchahid          #+#    #+#             */
/*   Updated: 2026/09/04 12:26:27 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	enqueue_coder(t_coder *coder, t_dongle *dongle)
{
	t_request	coder_request;

	coder_request.coder_id = coder->id;
	if (coder->data->args.scheduler == EDF)
	{
		pthread_mutex_lock(&coder->data->state_lock);
		coder_request.priority = coder->last_compiled_time;
		pthread_mutex_unlock(&coder->data->state_lock);
	}
	else
		coder_request.priority = get_current_time_ms();
	pthread_mutex(&dongle->pqueue_lock);
	pqueue_push(dongle->pqueue, coder_request);
	pthread_mutex(&dongle->pqueue_lock);
}

int		get_top_coder_id(t_heapq *pqueue)
{
	t_request	top;

	if (pqueue_peek(pqueue, &top) == true)
		return (top.coder_id);
	return (-1);
}

bool	take_dongles(t_coder *coder)
{
	if (!is_simulation_running(coder->data))
		return (false);
	pthread_mutex_lock(&coder->data->state_lock);
	enqueue_coder(coder, coder->left_dongle);
	enqueue_coder(coder, coder->right_dongle);
	while(!coder->left_dongle->is_available
		|| !coder->right_dongle->is_available
		|| get_top_coder_id(coder->left_dongle->pqueue) != coder->id
		|| get_top_coder_id(coder->right_dongle->pqueue) != coder->id)
	{
		pthread_cond_wait(&coder->data->table_cond, &coder->data->state_lock);
	}
	pqueue_pop(coder->left_dongle->pqueue, NULL);
	pqueue_pop(coder->right_dongle->pqueue, NULL);
	coder->left_dongle->is_available = false;
	coder->right_dongle->is_available = false;
	pthread_mutex_lock(&coder->left_dongle->lock);
	print_action(coder, "has taken a dongle");
	pthread_mutext_lock(&coder->right_dongle->lock);
	print_action(coder, "has taken a dongle");
	pthread_mutex_unlock(&coder->data->state_lock);
	return (true);
}

void	drop_dongles(t_coder *coder)
{
	long long	time_now;

	pthread_mutex_lock(&coder->data->state_lock);
	time_now = get_current_time_ms();
	coder->left_dongle->is_available = true;
	coder->left_dongle->last_released_time = time_now;
	coder->right_dongle->is_available = true;
	coder->right_dongle->last_released_time = time_now;
	pthread_mutex_unlock(&coder->left_dongle->lock);
	pthread_mutex_unlock(&coder->right_dongle->lock);
	pthread_cond_broadcast(&coder->data->table_cond);
	pthread_mutex_unlock(&coder->data->state_lock);
}