/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:53:29 by mbousset          #+#    #+#             */
/*   Updated: 2024/11/03 14:27:38 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putrstr_fd(char *s, int fd)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		ft_putchar_fd(s[i], fd);
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	res[12];
	int		i;
	int		sign;
	long	m;

	m = n;
	if (fd < 0)
		return ;
	sign = (m < 0);
	i = 0;
	if (m < 0)
		m = -m;
	if (m == 0)
		res[i++] = '0';
	while (m > 0)
	{
		res[i++] = m % 10 + 48;
		m /= 10;
	}
	if (sign)
		res[i++] = '-';
	res[i] = '\0';
	ft_putrstr_fd(res, fd);
}
