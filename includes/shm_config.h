/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shm_config.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndudnicz <ndudnicz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 11:56:04 by ndudnicz          #+#    #+#             */
/*   Updated: 2018/12/14 11:56:05 by ndudnicz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHM_CONFIG_H
# define SHM_CONFIG_H

# include "misc.h"
# include "config.h"
# include "error.h"

# define SHM_KEY	0x00e1d2f4

# if BOARD_SIZE <= 0
#  error BOARD_SIZE wrong value.
# endif

# define SHM_SIZE	(BOARD_SIZE * BOARD_SIZE)
# define SHM_FLAG	(IPC_CREAT)

#endif
