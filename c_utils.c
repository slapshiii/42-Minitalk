/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:26:29 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 16:05:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	is_whitespace(char c)
{
	if (c == 32 || (c < 14 && c > 8))
		return (1);
	return (0);
}

int	ft_atoi(const char *s)
{
	int	res;
	int	sig;

	res = 0;
	sig = -1;
	while (*s && is_whitespace(*s))
		++s;
	if (*s && *s == '-')
	{
		sig = 1;
		++s;
	}
	else if (*s && *s == '+')
		++s;
	while (*s && *s >= '0' && *s <= '9')
	{
		res = (res * 10) + (*s - '0');
		++s;
	}
	return (res * (-sig));
}

int	ft_isnum(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] > '9' || s[i] < '0')
			return (0);
		++i;
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*res;

	i = 0;
	len = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res)
	{
		while (s1[i])
		{
			res[i] = s1[i];
			++i;
		}
		res[i] = '\0';
	}
	return (res);
}
