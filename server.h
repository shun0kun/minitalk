#ifndef SERVER_H
# define DERVER_H

# define _POSIX_C_SOURCE	200809L

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_charbuf
{
	char	acc;
	int		count;
}	t_charbuf;

#endif
