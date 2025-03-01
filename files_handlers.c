/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:02:48 by mbousset          #+#    #+#             */
/*   Updated: 2025/03/01 18:08:56 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	read_from_herdoc(char *delemeter, int *old_fd)
{
	int	fd1;

	fd1 = create_temp_file(old_fd);
	process_input(fd1, delemeter);
	close(fd1);
}

char	*read_full_line(void)
{
	char	*line;
	char	*tmp;

	line = get_next_line(0);
	while (line && line[ft_strlen(line) - 1] != '\n')
	{
		tmp = NULL;
		while (!tmp)
			tmp = get_next_line(0);
		line = stor_line(tmp, line);
		free(tmp);
	}
	return (line);
}

int	create_temp_file(int *old_fd)
{
	int	fd1;

	fd1 = open("/tmp/temp_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	*old_fd = open("/tmp/temp_file", O_RDONLY);
	unlink("/tmp/temp_file");
	if (fd1 == -1 || *old_fd == -1)
		handle_error();
	return (fd1);
}

void	in_file_open(t_data *prg_data, char *path, int *old_fd)
{
	*old_fd = open(path, O_RDONLY);
	if (*old_fd == -1)
	{
		print_err(strerror(errno), path);
		ft_exit(prg_data, 1);
	}
}

void	out_file_open(t_data *prg_data, int in_her_doc, char *path, int *out_fd)
{
	if (!in_her_doc)
		*out_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*out_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*out_fd == -1)
	{
		print_err(strerror(errno), path);
		ft_exit(prg_data, 1);
	}
}
