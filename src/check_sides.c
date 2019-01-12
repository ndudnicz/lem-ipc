/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sides.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:11:13 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:11:14 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "board.h"
#include "mylimits.h"

t_u32	check_left(
t_player *p,
t_board *b
)
{
	if (p->x > 0)
	{
		return (b->b[p->y][p->x - 1] >= 0 ? b->b[p->y][p->x - 1] : SHORTMAX);
	}
	else
	{
		return (0);
	}
}

t_u32	check_right(
t_player *p,
t_board *b
)
{
	if (p->x < BOARD_SIZE - 1)
	{
		return (b->b[p->y][p->x + 1] >= 0 ? b->b[p->y][p->x + 1] : SHORTMAX);
	}
	else
	{
		return (0);
	}
}

t_u32	check_up(
t_player *p,
t_board *b
)
{
	if (p->y > 0)
	{
		return (b->b[p->y - 1][p->x] >= 0 ? b->b[p->y - 1][p->x] : SHORTMAX);
	}
	else
	{
		return (0);
	}
}

t_u32	check_down(
t_player *p,
t_board *b
)
{
	if (p->y < BOARD_SIZE - 1)
	{
		return (b->b[p->y + 1][p->x] >= 0 ? b->b[p->y + 1][p->x] : SHORTMAX);
	}
	else
	{
		return (0);
	}
}
