/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 09:29:10 by ndudnicz          #+#    #+#             */
/*   Updated: 2018/09/20 10:42:57 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libftasm.h"

void	*ft_calloc(
size_t const size
)
{
	void *const	ptr = malloc(size);

	if (ptr == NULL)
	{
		return (NULL);
	}
	else
	{
		return (ft_memset(ptr, 0, size));
	}
}
