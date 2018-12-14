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
** Not a true sleep, just something that will slows the execution
*/

void	ft_sleep(int second)
{
	int		i;
	int		n;

	n = 0;
	while (n < second)
	{
		i = 0;
		while (i < 500200000)
			i++;
		n++;
	}
}
