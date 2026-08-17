/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 16:48:40 by abchahid          #+#    #+#             */
/*   Updated: 2026/08/17 18:59:05 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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

typedef struct	s_dongle
{
	int			id;
	
} t_dongle;

typedef struct	s_data
{
	t_sim_args		args;
}	t_data;

typedef struct	s_request
{
	t_coder		coder;
	
}	t_request;

int		parse_args(int argc, char **argv, t_sim_args *args);
#endif