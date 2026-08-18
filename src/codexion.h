/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 16:48:40 by abchahid          #+#    #+#             */
/*   Updated: 2026/08/18 18:57:47 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum	e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct	s_sim_args
{
	int				nb_coders;
	int				burnout_time;
	int				compile_time;
	int				debug_time;
	int				refactor_time;
	int				compiles_req;
	int				cooldown_time;
	t_scheduler		scheduler;
}	t_sim_args;

typedef struct	s_coder
{
	int			id;
	long long	last_compiled;
}	t_coder;

typedef struct	s_request
{
	// t_coder		coder;
	int			coder_id;
	long long	priority;
}	t_request;

typedef struct	s_heapq
{
	t_request	*requests;
	int			capacity;
	int			size;
}	t_heapq;

typedef struct	s_dongle
{
	int				id;
	long long		last_released;
	t_heapq			pqueue;
	pthread_mutex_t	lock;
}	t_dongle;

typedef struct	s_data
{
	t_sim_args			args;
	t_dongle			*dongles;
	t_coder				*coders;
	bool				is_running;
	pthread_mutex_t		state_lock;
	pthread_mutex_t		print_lock;
	long long			sim_start_time;
	pthread_mutex_t		sim_start_lock;
	pthread_cond_t		sim_start_cond;
}	t_data;

bool		parse_args(int argc, char **argv, t_sim_args *args);
bool		init_data(t_data *data);
bool		pqueue_create(t_heapq *pqueue);
bool		pqueue_peek(t_heapq *pqueue, t_request *top);
bool		pqueue_push(t_heapq *pqueue, t_request *request);
bool		pqueue_pop(t_heapq *pqueue, t_request *top);
long long	get_current_time_ms(void);
void		ft_usleep(long long wait_time, t_data *data);

#endif