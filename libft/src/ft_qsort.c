/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:48:33 by ndudnicz          #+#    #+#             */
/*   Updated: 2018/04/05 15:51:58 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		swap(void **a, void **b)
{
	void	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/*
** Source: https://en.wikipedia.org/wiki/Quicksort
*/

static int		partition(void **array, int start, int end,
							int (*compare)(void*, void*))
{
	int		j;
	int		i;
	void	*pivot;

	pivot = array[end];
	i = start - 1;
	j = start;
	while (j < end)
	{
		if (compare(array[j], pivot))
		{
			i++;
			swap(&array[i], &array[j]);
		}
		j++;
	}
	if (compare(array[end], array[i + 1]))
		swap(&array[i + 1], &array[end]);
	return (i + 1);
}

void			ft_qsort(void **array, int start, int end,
							int (*compare)(void*, void*))
{
	int		pivot;

	if (start < end)
	{
		pivot = partition(array, start, end, compare);
		ft_qsort(array, start, pivot - 1, compare);
		ft_qsort(array, pivot + 1, end, compare);
	}
}
