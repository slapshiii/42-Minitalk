/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 11:06:25 by user42            #+#    #+#             */
/*   Updated: 2021/09/16 19:44:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		tmp[i] = (unsigned char)c;
		++i;
	}
	return (s);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

static char	*reverse(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		c = str[i];
		str[i] = str[j];
		str[j] = c;
		++i;
		--j;
	}
	return (str);
}

char	*ft_itoa(int n, char *str, int base)
{
	int	i;
	int	sign;

	if (n < 0)
	{
		sign = -1;
		n = -n;
	}
	else
		sign = 0;
	i = 0;
	while (n > 0)
	{
		str[i++] = n % base + '0';
		n /= base;
	}
	if (sign == -1)
		str[i++] = '-';
	str[i] = '\0';
	return (reverse(str));
}

char	*realloc_s(char *ptr, size_t prev_size, size_t new_size)
{
	char	*res;
	size_t	i;

	if (prev_size > new_size)
		return (ptr);
	res = (char *)malloc(sizeof(char) * new_size);
	if (res == NULL)
		exit (1);
	ft_memset(res, 0, new_size);
	if (!ptr)
		return (res);
	i = 0;
	while (i < prev_size)
	{
		res[i] = ptr[i];
		++i;
	}
	free(ptr);
	return (res);
}
