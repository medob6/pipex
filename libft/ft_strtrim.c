/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:19:24 by mbousset          #+#    #+#             */
/*   Updated: 2024/11/03 12:49:06 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	check_char(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*res;

	start = 0;
	if (!str || !set)
		return ((char *)str);
	end = ft_strlen(str) - 1;
	while (str[start] && check_char(str[start], set))
		start++;
	while ((start < end) && check_char(str[end], set))
		end--;
	res = malloc((end - start + 2) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (start < (end + 1))
		res[i++] = str[start++];
	res[i] = '\0';
	return (res);
}
