/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:13:02 by ndudnicz          #+#    #+#             */
/*   Updated: 2019/01/11 16:13:04 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "error.h"
#include "mystdint.h"

t_s32	ft_error_ret(
	char const *s1,
	char const *s2,
	char const *s3,
	t_s32 const ret
)
{
	char	*s;

	s = NULL;
	asprintf(&s, "%s%s%s", s1 ? s1 : "", s2 ? s2 : "", s3 ? s3 : "");
	ft_putstr_fd(s, 2);
	free(s);
	return (ret);
}
