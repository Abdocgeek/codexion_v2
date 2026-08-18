/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:43:33 by abchahid          #+#    #+#             */
/*   Updated: 2026/08/18 18:50:33 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_action(t_data *data, int coder_id, char *msg)
{
	pthread_mutex_lock(&data->print_lock);
	printf("%d %d %s",  coder_id, msg);
	pthread_mutex_unlock(&data->print_lock);
}
void	do_compile(t_data *data, t_coder *coder)
{
	
}

