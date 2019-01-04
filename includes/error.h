#ifndef ERROR_HPP
# define ERROR_HPP

# include "mystdint.h"

# define BOARD_SIZE_TOO_BIG "BOARD_SIZE too big.\n"
# define INVALID_TEAM_NUMBER "Invalid team number.\n"

t_s32	ft_error_ret(
	char const *s1,
	char const *s2,
	char const *s3,
	t_s32 const ret
);

#endif
