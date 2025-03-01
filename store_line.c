/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 14:07:48 by mbousset          #+#    #+#             */
/*   Updated: 2025/03/01 17:52:41 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*stor_line(char *line, char *buf)
{
	char	*new_buf;

	new_buf = ft_strjoin(buf, line);
	free(buf);
	return (new_buf);
}

void	free_garbeg(t_data *prg_data)
{
	int	i;

	i = 0;
	while (i < prg_data->cmd_nbr)
	{
		free(prg_data->lst_cmd[i].path);
		free_all(prg_data->lst_cmd[i].args);
		i++;
	}
	free(prg_data->lst_cmd);
	get_next_line(-1);
}

void	ft_exit(t_data *prg_data, int status)
{
	free_garbeg(prg_data);
	exit(status);
}
