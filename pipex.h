#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char *path;
	char	**args;
	pid_t	pid;
	int		exit_status;

}			t_cmd;
typedef struct s_data
{
	int		old_fd;
	int		out_fd;
	int		cmd_nbr;
	int		in_her_doc;
	char	*buf;
	t_cmd	*lst_cmd;
}			t_data;

#endif