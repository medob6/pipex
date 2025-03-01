#ifndef PIPEX_H
# define PIPEX_H

# include "utils_lib/libft.h"
# include "utils_lib/get_next_line.h"
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
	char	*path;
	char	**args;
	pid_t	pid;
	int		exit_status;

}			t_cmd;
typedef struct s_data
{
	int		old_fd;
	int		out_fd;
	int		fd[2];
	t_cmd	*lst_cmd;
	int		cmd_nbr;
	char	**envp;
	int		ac;
}			t_data;


/* FUNCTIONS */
void	print_err(char *err, char *str)
;
char	*join_strings(char *s, ...)
;

#endif