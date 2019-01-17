/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 12:32:00 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/17 12:32:02 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "board.h"

t_s32	player_suicide(
t_player *p,
t_board *board
)
{
	if (board == NULL)
	{
		if ((int)(board = (t_board *)shmat(p->ipcs.shmid, NULL, 0)) < 0)
			exit(ft_error_ret("Error: ", FAIL_SHMAT, NULL, EXIT_FAILURE));
		else
		{
			board->n_player--;
			shmdt(board);
		}
	}
	else
	{
		board->n_player--;
	}
	return (0);
}
