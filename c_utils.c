/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:26:29 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 19:02:09 by user42           ###   ########.fr       */
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
