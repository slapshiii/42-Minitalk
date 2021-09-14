/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 10:04:36 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 18:09:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>

# include <stdio.h>

# define TRUE 1
# define FALSE 0

# define USR1 0
# define USR2 1

typedef struct s_client
{
	pid_t	s_pid;
	int		bit;
	int		len;
	char	*msg;
}	t_client;

int	is_whitespace(char c);
int	ft_atoi(const char *s);

#endif