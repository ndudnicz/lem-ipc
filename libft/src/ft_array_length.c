/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 18:45:53 by ndudnicz          #+#    #+#             */
/*   Updated: 2017/11/02 18:45:54 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_array_length(char const **array)
{
	int		i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}
