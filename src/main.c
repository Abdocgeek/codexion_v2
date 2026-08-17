/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchahid <abchahid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 17:10:23 by abchahid          #+#    #+#             */
/*   Updated: 2026/08/17 18:54:36 by abchahid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_data		data;

	if (parse_args(argc, argv, &data.args) == 1)
	{
		printf("Error: Wrong parameters!");
		return (1);
	}
}