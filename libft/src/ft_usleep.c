/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/04 16:52:27 by ndudnicz          #+#    #+#             */
/*   Updated: 2016/01/04 16:56:04 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Not a true usleep, just something that will slows the execution
*/

void	ft_usleep(int msecond)
{
	int		i;
	int		n;

	n = 0;
	while (n < msecond)
	{
		i = 0;
		while (i < 500200)
			i++;
		n++;
	}
}
